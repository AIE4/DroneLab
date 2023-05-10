/*
 * Config.h
 *
 *  Created on: 7 May 2023
 *      Author: Mateusz Matejko
 */

#ifndef INC_CONFIG_H_
#define INC_CONFIG_H_

//these 2 have to be 1 in addition! (times 100)
#define CONFIG_COMPLEMENTARY_FILTER_GyroPart 95
#define CONFIG_COMPLEMENTARY_FILTER_AccelPart 5

#if CONFIG_COMPLEMENTARY_FILTER_GyroPart + CONFIG_COMPLEMENTARY_FILTER_AccelPart != 100
#error "Complementary filter values are not 1 in addition"
#endif

#define CONFIG_MaximumITerm 400

#endif /* INC_CONFIG_H_ */
