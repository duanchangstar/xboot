/*
 * kernel/command/cmd_exit.c
 *
 * Copyright (c) 2007-2008  jianjun jiang <jjjstudio@gmail.com>
 * official site: http://xboot.org
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 */

#include <configs.h>
#include <default.h>
#include <types.h>
#include <string.h>
#include <malloc.h>
#include <mode/mode.h>
#include <xboot/log.h>
#include <xboot/list.h>
#include <xboot/printk.h>
#include <xboot/initcall.h>
#include <command/command.h>

#if	defined(CONFIG_COMMAND_EXIT) && (CONFIG_COMMAND_EXIT > 0)

static void usage(void)
{
	printk("usage:\r\n");
	printk("    exit [-n|-s|-m|-g|-e]\r\n");
	printk("    exit [--normal|--shell|--menu|--graphic|--extend]\r\n");
}

static x_s32 exit_to_mode(x_s32 argc, const x_s8 **argv)
{
	if(argc == 1)
	{
		xboot_set_mode(MODE_MENU);
	}
	else if(argc == 2)
	{
		if( (strcmp(argv[1], (x_s8*)"-n") == 0) || (strcmp(argv[1], (x_s8*)"--normal") == 0) )
		{
			xboot_set_mode(MODE_NORMAL);
		}
		else if( (strcmp(argv[1], (x_s8*)"-s") == 0) || (strcmp(argv[1], (x_s8*)"--shell") == 0) )
		{
			xboot_set_mode(MODE_SHELL);
		}
		else if( (strcmp(argv[1], (x_s8*)"-m") == 0) || (strcmp(argv[1], (x_s8*)"--menu") == 0) )
		{
			xboot_set_mode(MODE_MENU);
		}
		else if( (strcmp(argv[1], (x_s8*)"-g") == 0) || (strcmp(argv[1], (x_s8*)"--graphic") == 0) )
		{
			xboot_set_mode(MODE_GRAPHIC);
		}
		else if( (strcmp(argv[1], (x_s8*)"-e") == 0) || (strcmp(argv[1], (x_s8*)"--extend") == 0) )
		{
			xboot_set_mode(MODE_EXTEND);
		}
		else
		{
			usage();
			return -1;
		}
	}
	else
	{
		usage();
		return -1;
	}

	return 0;
}

static struct command exit_cmd = {
	.name		= "exit",
	.func		= exit_to_mode,
	.desc		= "exit to another system mode\r\n",
	.usage		= "exit [-n|-s|-m|-g|-e]\r\n",
	.help		= "    exit to another system mode.\r\n"
				  "    no arguments for enter to menu mode.\r\n"
				  "    -n | --normal    enter to normal mode\r\n"
				  "    -s | --shell     enter to shell mode\r\n"
				  "    -m | --menu      enter to menu mode\r\n"
				  "    -g | --graphic   enter to graphic mode\r\n"
				  "    -e | --extend    enter to extend mode\r\n"
};

static __init void exit_cmd_init(void)
{
	if(!command_register(&exit_cmd))
		LOG_E("register 'exit' command fail");
}

static __exit void exit_cmd_exit(void)
{
	if(!command_unregister(&exit_cmd))
		LOG_E("unregister 'exit' command fail");
}

module_init(exit_cmd_init, LEVEL_COMMAND);
module_exit(exit_cmd_exit, LEVEL_COMMAND);

#endif
