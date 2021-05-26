#! /usr/bin/env python

import extargsparse
import logging
import sys
import os
import re
import platform

def set_log_level(args):
    loglvl= logging.ERROR
    if args.verbose >= 3:
        loglvl = logging.DEBUG
    elif args.verbose >= 2:
        loglvl = logging.INFO
    elif args.verbose >= 1 :
        loglvl = logging.WARN
    # we delete old handlers ,and set new handler
    if logging.root is not None and logging.root.handlers is not None and len(logging.root.handlers) > 0:
    	logging.root.handlers = []
    logging.basicConfig(level=loglvl,format='%(asctime)s:%(filename)s:%(funcName)s:%(lineno)d\t%(message)s')
    return

def read_file(infile=None):
	fin = sys.stdin
	if infile is not None:
		fin = open(infile,'r+b')
	rets = ''
	for l in fin:
		s = l
		if 'b' in fin.mode:
			if sys.version[0] == '3':
				s = l.decode('utf-8')
		rets += s

	if fin != sys.stdin:
		fin.close()
	fin = None
	return rets

def write_file(s,outfile=None):
	fout = sys.stdout
	if outfile is not None:
		fout = open(outfile, 'w+b')
	outs = s
	if 'b' in fout.mode:
		outs = s.encode('utf-8')
	fout.write(outs)
	if fout != sys.stdout:
		fout.close()
	fout = None
	return 


def is_in_windows():
	s = platform.system().lower()
	if s == 'windows':
		return True
	return False

def checkenvpath_handler(args,parser):
	ok = True
	set_log_level(args)
	envpath = os.environ[args.subnargs[0]]
	if is_in_windows():
		csarr = re.split(';',envpath)
	else:
		csarr = re.split(':',envpath)
	sarr = []
	for l in csarr:
		if is_in_windows():
			l = l.lower()
		sarr.append(l)
	for p in args.subnargs[1:]:
		if is_in_windows():
			p = p.lower()
		if p not in sarr:
			ok = False
			logging.error('[%s] not in [%s]'%(p,args.subnargs[0]))
			break
	if ok:
		sys.exit(0)
	else:
		sys.exit(1)
	return

def remove_quiet_file(fname,verbose):
	reads = read_file(fname)
	sarr = re.split('\n',reads)
	writes = ''
	matchexpr = re.compile('^\t@')
	idx = 0
	removed = 0
	for l in sarr:
		idx += 1
		#l = l.rstrip('\r\n')
		if matchexpr.match(l):
			s = l.replace('@','',1)
			logging.debug('replace [%d][%s] => [%s]'%(idx,l,s))
			l = s
			removed += 1
		writes += '%s\n'%(l)
	write_file(writes,fname)
	return removed



def remove_quiet_dir(dname,recursive,filters,dryrun,verbose=0):
	files = os.listdir(dname)
	retval = 0
	for f in files:
		if f != '.' and f != '..':
			curf = os.path.join(dname,f)
			if f in filters:
				rdline = 0
				if not dryrun:
					rdline = remove_quiet_file(curf,verbose)
				logging.info('removed [%s] [%s]'%(curf,rdline))
				retval += 1
			if os.path.isdir(curf) and recursive:
				retval += remove_quiet_dir(curf,recursive,filters,dryrun,verbose)
	return retval

def removequiet_handler(args,parser):
	set_log_level(args)
	filters = args.subnargs
	dname = os.path.abspath(args.dstdir)
	retval = remove_quiet_dir(dname,args.recursive,filters, args.dryrun,args.verbose)
	sys.stdout.write('remove [%s]\n'%(retval))
	sys.exit(0)
	return


def main():
	commandline_fmt='''
	{
		"verbose|v" : "+",
		"dstdir|D" : "%s",
		"recursive|R" : true,
		"dryrun" : false,
		"checkenvpath<checkenvpath_handler>##envvar paths ... to check paths in the envvar##" : {
			"$" : "+"
		},
		"removequiet<removequiet_handler>##fnames ... to get file names##" : {
			"$" : "+"
		}
	}
	'''
	curd = os.getcwd()
	commandline = commandline_fmt%(curd.replace('\\','\\\\'))
	parser = extargsparse.ExtArgsParse()
	parser.load_command_line_string(commandline)
	parser.parse_command_line(None,parser)
	raise Exception('can not go here')
	return

main()