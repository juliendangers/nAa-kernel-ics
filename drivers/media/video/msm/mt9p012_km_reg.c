/* Copyright (c) 2009-2010, Code Aurora Forum. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of Code Aurora Forum nor
 *       the names of its contributors may be used to endorse or promote
 *       products derived from this software without specific prior written
 *       permission.
 *
 * Alternatively, provided that this notice is retained in full, this software
 * may be relicensed by the recipient under the terms of the GNU General Public
 * License version 2 ("GPL") and only version 2, in which case the provisions of
 * the GPL apply INSTEAD OF those given above.  If the recipient relicenses the
 * software under the GPL, then the identification text in the MODULE_LICENSE
 * macro must be changed to reflect "GPLv2" instead of "Dual BSD/GPL".  Once a
 * recipient changes the license terms to the GPL, subsequent recipients shall
 * not relicense under alternate licensing terms, including the BSD or dual
 * BSD/GPL terms.  In addition, the following license statement immediately
 * below and between the words START and END shall also then apply when this
 * software is relicensed under the GPL:
 *
 * START
 *
 * This program is free software; you can redistribute it and/or modify it under
 * the terms of the GNU General Public License version 2 and only version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 * END
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 */

#include "mt9p012_km.h"
#include <linux/kernel.h>

/*Micron settings from Applications for lower power consumption.*/
struct reg_struct const mt9p012_km_reg_pat[2] = {
	{ /* Preview */
		/* vt_pix_clk_div          REG=0x0300 */
		6,  /* 5 */

		/* vt_sys_clk_div          REG=0x0302 */
		1,

		/* pre_pll_clk_div         REG=0x0304 */
		2,

		/* pll_multiplier          REG=0x0306 */
		60,

		/* op_pix_clk_div          REG=0x0308 */
		8,  /* 10 */

		/* op_sys_clk_div          REG=0x030A */
		1,

		/* scale_m                 REG=0x0404 */
		16,

		/* row_speed               REG=0x3016 */
		0x0111,

		/* x_addr_start            REG=0x3004 */
		8,

		/* x_addr_end              REG=0x3008 */
		2597,

		/* y_addr_start            REG=0x3002 */
		8,

		/* y_addr_end              REG=0x3006 */
		1949,

		/* read_mode               REG=0x3040
		 * Preview 2x2 skipping */
		0x006C,

		/* x_output_size           REG=0x034C */
		1296,

		/* y_output_size           REG=0x034E */
		972,

		/* line_length_pck         REG=0x300C */
		3783,

		/* frame_length_lines      REG=0x300A */
		1074,

		/* coarse_integration_time REG=0x3012 */
		16,

		/* fine_integration_time   REG=0x3014 */
		1764
	},
	{ /* Snapshot */
		/* vt_pix_clk_div          REG=0x0300 */
		6,

		/* vt_sys_clk_div          REG=0x0302 */
		1,

		/* pre_pll_clk_div         REG=0x0304 */
		2,

		/* pll_multiplier          REG=0x0306
		 * 39 for 10fps snapshot */
		39,

		/* op_pix_clk_div          REG=0x0308 */
		8,

		/* op_sys_clk_div          REG=0x030A */
		1,

		/* scale_m                 REG=0x0404 */
		16,

		/* row_speed               REG=0x3016 */
		0x0111,

		/* x_addr_start            REG=0x3004 */
		8,

		/* x_addr_end              REG=0x3008 */
		2615,

		/* y_addr_start            REG=0x3002 */
		8,

		/* y_addr_end              REG=0x3006 */
		1967,

		/* read_mode               REG=0x3040 */
		0x0024,

		/* x_output_size           REG=0x034C */
		2608,

		/* y_output_size           REG=0x034E */
		1960,

		/* line_length_pck         REG=0x300C */
		3788,

		/* frame_length_lines      REG=0x300A 10 fps snapshot */
		2045,

		/* coarse_integration_time REG=0x3012 */
		16,

		/* fine_integration_time   REG=0x3014 */
		882
	}
};

struct mt9p012_km_i2c_reg_conf const mt9p012_km_test_tbl[] = {
	{0x3044, 0x0544 & 0xFBFF},
	{0x30CA, 0x0004 | 0x0001},
	{0x30D4, 0x9020 & 0x7FFF},
	{0x31E0, 0x0003 & 0xFFFE},
	{0x3180, 0x91FF & 0x7FFF},
	{0x301A, (0x10CC | 0x8000) & 0xFFF7},
	{0x301E, 0x0000},
	{0x3780, 0x0000},
};


struct mt9p012_km_i2c_reg_conf const mt9p012_km_lc_tbl[] = {
	{0x360A, 0x00F0},
	{0x360C, 0x0B29},
	{0x360E, 0x5ED1},
	{0x3610, 0x890D},
	{0x3612, 0x9871},
	{0x364A, 0xAD2C},
	{0x364C, 0x0A8C},
	{0x364E, 0x91EC},
	{0x3650, 0x94EC},
	{0x3652, 0xC76B},
	{0x368A, 0x5931},
	{0x368C, 0x4FED},
	{0x368E, 0x8A50},
	{0x3690, 0x5C0F},
	{0x3692, 0x8393},
	{0x36CA, 0xDB8E},
	{0x36CC, 0xCA4D},
	{0x36CE, 0x146F},
	{0x36D0, 0x618F},
	{0x36D2, 0x014F},
	{0x370A, 0x1FEE},
	{0x370C, 0xDD50},
	{0x370E, 0xDB54},
	{0x3710, 0xCA92},
	{0x3712, 0x1896},
	{0x3600, 0x00F0},
	{0x3602, 0xA04C},
	{0x3604, 0x5711},
	{0x3606, 0x5E6D},
	{0x3608, 0xA971},
	{0x3640, 0xDCCC},
	{0x3642, 0x0529},
	{0x3644, 0x96ED},
	{0x3646, 0xF447},
	{0x3648, 0x4AEE},
	{0x3680, 0x2171},
	{0x3682, 0x634F},
	{0x3684, 0xCC91},
	{0x3686, 0xA9CE},
	{0x3688, 0x8751},
	{0x36C0, 0x8B6D},
	{0x36C2, 0xE20E},
	{0x36C4, 0x750F},
	{0x36C6, 0x0090},
	{0x36C8, 0x9E91},
	{0x3700, 0xEAAF},
	{0x3702, 0xB8AF},
	{0x3704, 0xE293},
	{0x3706, 0xAB33},
	{0x3708, 0x4595},
	{0x3614, 0x00D0},
	{0x3616, 0x8AAB},
	{0x3618, 0x18B1},
	{0x361A, 0x54AD},
	{0x361C, 0x9DB0},
	{0x3654, 0x11EB},
	{0x3656, 0x332C},
	{0x3658, 0x316D},
	{0x365A, 0xF0EB},
	{0x365C, 0xB4ED},
	{0x3694, 0x0F31},
	{0x3696, 0x08D0},
	{0x3698, 0xA52F},
	{0x369A, 0xE64F},
	{0x369C, 0xC9D2},
	{0x36D4, 0x8C2D},
	{0x36D6, 0xAD6E},
	{0x36D8, 0xE1CE},
	{0x36DA, 0x1750},
	{0x36DC, 0x8CAD},
	{0x3714, 0x8CAF},
	{0x3716, 0x8C11},
	{0x3718, 0xE453},
	{0x371A, 0x9693},
	{0x371C, 0x38B5},
	{0x361E, 0x00D0},
	{0x3620, 0xB6CB},
	{0x3622, 0x4811},
	{0x3624, 0xB70C},
	{0x3626, 0xA771},
	{0x365E, 0xB5A9},
	{0x3660, 0x05AA},
	{0x3662, 0x00CF},
	{0x3664, 0xB86B},
	{0x3666, 0xA4AF},
	{0x369E, 0x3E31},
	{0x36A0, 0x902B},
	{0x36A2, 0xD251},
	{0x36A4, 0x5C2F},
	{0x36A6, 0x8471},
	{0x36DE, 0x2C6D},
	{0x36E0, 0xECEE},
	{0x36E2, 0xB650},
	{0x36E4, 0x0210},
	{0x36E6, 0xACAE},
	{0x371E, 0xAC30},
	{0x3720, 0x394E},
	{0x3722, 0xFDD3},
	{0x3724, 0xBCB2},
	{0x3726, 0x5AD5},
	{0x3782, 0x0508},
	{0x3784, 0x03B4},
	{0x3780, 0x8000},
};

struct mt9p012_km_i2c_reg_conf const mt9p012_km_rolloff_tbl[] = {
	{0x360A, 0x00F0},
	{0x360C, 0x0B29},
	{0x360E, 0x5ED1},
	{0x3610, 0x890D},
	{0x3612, 0x9871},
	{0x364A, 0xAD2C},
	{0x364C, 0x0A8C},
	{0x364E, 0x91EC},
	{0x3650, 0x94EC},
	{0x3652, 0xC76B},
	{0x368A, 0x5931},
	{0x368C, 0x4FED},
	{0x368E, 0x8A50},
	{0x3690, 0x5C0F},
	{0x3692, 0x8393},
	{0x36CA, 0xDB8E},
	{0x36CC, 0xCA4D},
	{0x36CE, 0x146F},
	{0x36D0, 0x618F},
	{0x36D2, 0x014F},
	{0x370A, 0x1FEE},
	{0x370C, 0xDD50},
	{0x370E, 0xDB54},
	{0x3710, 0xCA92},
	{0x3712, 0x1896},
	{0x3600, 0x00F0},
	{0x3602, 0xA04C},
	{0x3604, 0x5711},
	{0x3606, 0x5E6D},
	{0x3608, 0xA971},
	{0x3640, 0xDCCC},
	{0x3642, 0x0529},
	{0x3644, 0x96ED},
	{0x3646, 0xF447},
	{0x3648, 0x4AEE},
	{0x3680, 0x2171},
	{0x3682, 0x634F},
	{0x3684, 0xCC91},
	{0x3686, 0xA9CE},
	{0x3688, 0x8751},
	{0x36C0, 0x8B6D},
	{0x36C2, 0xE20E},
	{0x36C4, 0x750F},
	{0x36C6, 0x0090},
	{0x36C8, 0x9E91},
	{0x3700, 0xEAAF},
	{0x3702, 0xB8AF},
	{0x3704, 0xE293},
	{0x3706, 0xAB33},
	{0x3708, 0x4595},
	{0x3614, 0x00D0},
	{0x3616, 0x8AAB},
	{0x3618, 0x18B1},
	{0x361A, 0x54AD},
	{0x361C, 0x9DB0},
	{0x3654, 0x11EB},
	{0x3656, 0x332C},
	{0x3658, 0x316D},
	{0x365A, 0xF0EB},
	{0x365C, 0xB4ED},
	{0x3694, 0x0F31},
	{0x3696, 0x08D0},
	{0x3698, 0xA52F},
	{0x369A, 0xE64F},
	{0x369C, 0xC9D2},
	{0x36D4, 0x8C2D},
	{0x36D6, 0xAD6E},
	{0x36D8, 0xE1CE},
	{0x36DA, 0x1750},
	{0x36DC, 0x8CAD},
	{0x3714, 0x8CAF},
	{0x3716, 0x8C11},
	{0x3718, 0xE453},
	{0x371A, 0x9693},
	{0x371C, 0x38B5},
	{0x361E, 0x00D0},
	{0x3620, 0xB6CB},
	{0x3622, 0x4811},
	{0x3624, 0xB70C},
	{0x3626, 0xA771},
	{0x365E, 0xB5A9},
	{0x3660, 0x05AA},
	{0x3662, 0x00CF},
	{0x3664, 0xB86B},
	{0x3666, 0xA4AF},
	{0x369E, 0x3E31},
	{0x36A0, 0x902B},
	{0x36A2, 0xD251},
	{0x36A4, 0x5C2F},
	{0x36A6, 0x8471},
	{0x36DE, 0x2C6D},
	{0x36E0, 0xECEE},
	{0x36E2, 0xB650},
	{0x36E4, 0x0210},
	{0x36E6, 0xACAE},
	{0x371E, 0xAC30},
	{0x3720, 0x394E},
	{0x3722, 0xFDD3},
	{0x3724, 0xBCB2},
	{0x3726, 0x5AD5},
	{0x3782, 0x0508},
	{0x3784, 0x03B4},
	{0x3780, 0x8000},
};


struct mt9p012_km_reg mt9p012_km_regs = {
	.reg_pat = &mt9p012_km_reg_pat[0],
	.reg_pat_size = ARRAY_SIZE(mt9p012_km_reg_pat),
	.ttbl = &mt9p012_km_test_tbl[0],
	.ttbl_size = ARRAY_SIZE(mt9p012_km_test_tbl),
	.lctbl = &mt9p012_km_lc_tbl[0],
	.lctbl_size = ARRAY_SIZE(mt9p012_km_lc_tbl),
	.rftbl = &mt9p012_km_rolloff_tbl[0],
	.rftbl_size = ARRAY_SIZE(mt9p012_km_rolloff_tbl)
};


