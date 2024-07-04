/*
 * myLib.c
 *
 *  Created on: Jul 4, 2024
 *      Author: boysb
 */
#include "main.h"

extern UART_HandleTypeDef huart2;
// Externally declared.
// It's in another .c file, so you just have to write it.

int __io_putchar(int ch)
// __ It's a system function that has a lot of underlines. Output to ports in 1-character units
{
	HAL_UART_Transmit(&huart2, &ch, 1, 10);
// *Write &(address) to express. uint8_t is 8 bit char. on a ms basis.
// When attached to the MSB side, Little endian (intel Cpu) If you stick to the LSB side, Big endian
// It goes backwards in Byte units. It goes in the order of L,1,2,3.
	return ch;
}
int __io_getchar(void)
{
	char ch;
// If it's int, it's 4 bytes (ch,0,0,0) and it's not compared, so I changed it to char.
	while(HAL_UART_Receive(&huart2, &ch, 1, 10) != HAL_OK);
	// HAL_UART_Receive(&huart2, &ch, 1, 10);
// Transmit one at a time, receive the receive and throw it all at once
// Receive causes an error because it has a timeout of 10ms.
// You have to keep it indefinitely until the price comes in.
	HAL_UART_Transmit(&huart2, &ch, 1, 10);
// The receive action allows PuTTy's keyboard input action to fall to STM32 as it is. Feedback.
// Make it happen at the same time. The keyboard value pressed on the screen is shown as it is.
// This is called echo.
// You must put the value of the enter into the input buffer.
	if(ch == '\r') HAL_UART_Transmit(&huart2, "\n", 1, 10);
// \r When CR is entered \n Please enter LF.
	return ch;
}
void ProgramStart()
{
	printf("\033[2J\033[1;1H\n");
// \033[ : escape sequence. 2J : Screen Initialization (Clear).
// y;xH : Move the cursor to the (x,y) position
	// printf("\033[2J\n");
	// printf("\033[1;1H\n");
// Same as the two lines above
	printf("Program Ready. Press Blue Button to Start\r\n");
	while(HAL_GPIO_ReadPin(B1_GPIO_Port, B1_Pin) != 0);
// B1 for Start
}

