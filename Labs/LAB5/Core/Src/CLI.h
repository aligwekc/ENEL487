/*
 * CLI.h
 *
 *  Created on: Dec. 8, 2020
 *      Author: Aligwekwe Chiamaka
 */

#ifndef SRC_CLI_H_
#define SRC_CLI_H_

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

const static char* prompt = "cmd> ";
#define CLEAR "\x1b[2J"
#define RC(r,c) "\x1b[" #r ";" #c "f"
#define ROLL_TO_BOTTOM(r) "\x1b[" #r ";r"
#define SAVE_CURSOR "\x1b[s"
#define RESTORE_CURSOR "\x1b[u"
#define MAX_USER_INPUT  100
#define forward "\x1b[1C"


uint8_t cliBufferTx[MAX_USER_INPUT];
uint8_t cliBufferRx[MAX_USER_INPUT];
uint8_t cliRXChar[5];



void printStringBlocking(const char* message);

#endif /* SRC_CLI_H_ */
