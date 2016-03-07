/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaz <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/10/04 11:43:01 by zaz               #+#    #+#             */
/*   Updated: 2016/03/07 18:13:22 by pciavald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"

t_op    op_tab[17] =
{
/*	mnemonic	nb args		args type												opcode	cycles	description									?		?	*/

	{"live",	1,			{T_DIR},												1,		10,		"alive",									0,		0},
	{"ld",		2,			{T_DIR | T_IND, T_REG},									2,		5,		"load",										1,		0},
	{"st",		2,			{T_REG, T_IND | T_REG},									3,		5,		"store",									1,		0},
	{"add",		3,			{T_REG, T_REG, T_REG},									4,		10,		"addition",									1,		0},
	{"sub",		3,			{T_REG, T_REG, T_REG},									5,		10,		"soustraction",								1,		0},
	{"and",		3,			{T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG},	6,		6,		"et (and	r1, r2, r3	r1 & r2 -> r3",		1,		0},
	{"or",		3,			{T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG},	7,		6,		"ou  (or	r1, r2, r3	r1 | r2 -> r3",		1,		0},
	{"xor",		3,			{T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG},	8,		6,		"ou (xor	r1, r2, r3	r1 ^ r2 -> r3",		1,		0},
	{"zjmp",	1,			{T_DIR},												9,		20,		"jump if zero",								0,		1},
	{"ldi",		3,			{T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG},			10,		25,		"load index",								1,		1},
	{"sti",		3,			{T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG},			11,		25,		"store index",								1,		1},
	{"fork",	1,			{T_DIR},												12,		800,	"fork",										0,		1},
	{"lld",		2,			{T_DIR | T_IND, T_REG},									13,		10,		"long load",								1,		0},
	{"lldi",	3,			{T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG},			14,		50, 	"long load index",							1,		1},
	{"lfork",	1,			{T_DIR},												15,		1000,	"long fork",								0,		1},
	{"aff",		1,			{T_REG},												16,		2,		"aff",										1,		0},
	{0,			0,			{0},													0,		0,		0,											0,		0}
};

/*
	r2,23,%34	0b01111000		0x78
	23,45,%34	0b11111000		0xF8
	r1,r3, 34	0b01011100		0x5C

	r2,23,%34	OCP 0x78		0x02 0x00 0x17 0x00 0x00 0x00 0x22
	23,45,%34	OCP 0xF8		0x00 0x17 0x00 0x2d 0x00 0x00 0x00 0x22


	.name "zork"
	.comment "just a basic living prog"

	l2:		sti		r1,		%:live,		%1
			and		r1,		%0,			r1
	live: 	live	%1
			zjmp	%:live

	Executable compile:
	
	0x0b,0x68,0x01,0x00,0x0f,0x00,0x01
	0x06,0x64,0x01,0x00,0x00,0x00,0x00,0x01
	0x01,0x00,0x00,0x00,0x01
	0x09,0xff,0xfb

*/
