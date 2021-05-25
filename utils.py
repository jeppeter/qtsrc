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


def main():
	commandline='''
	{
		"verbose|v" : "+",
		"checkenvpath<checkenvpath_handler>##envvar paths ... to check paths in the envvar##" : {
			"$" : "+"
		}
	}
	'''
	parser = extargsparse.ExtArgsParse()
	parser.load_command_line_string(commandline)
	parser.parse_command_line(None,parser)
	raise Exception('can not go here')
	return

main()