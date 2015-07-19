#include "stm32f4xx_it.h"
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_gpio.h"
#include "LED.h"
#include "Timer.h"
#include "Button.h"
#include "State.h"
#include "Yield.h"
#include "LedSM.h"
#include "ButtonSM.h"
#include "Message.h"
#include "Task.h"

void taskSwitch(void);

int main(void)	{
	initSysTick();
	initTcb();
	taskSwitch();

    while(1){}
}

void initSysTick()	{
	if(SysTick_Config(SystemCoreClock / 1000))	{
		//Capture error
		while(1);
	}
}

void LED1(TaskBlock *tb)	{

	startTask(tb);
	while(1)	{
		turnOnLED1();

		while(halfSecHasNotExpired())	{
			yield(tb);
		}

		turnOffLED1();

		while(halfSecHasNotExpired())	{
			yield(tb);
		}
	}
	endTask(x);
}

void LED2(TaskBlock *tb2)	{

	startTask(tb2);
	while(1)	{
		turnOnLED2();

		while(oneHundredMiliSecHasNotExpired())	{
			yield(tb2);
		}

		turnOffLED2();

		while(oneHundredMiliSecHasNotExpired())	{
			yield(tb2);
		}
	}
	endTask(x);
}

void LED3(TaskBlock *tb3)	{
	static int i = 0, count = 0;

	startTask(tb3);

	while(1)	{
		if(buttonStat())	{

			while(count < 5)	{
				turnOnLED3();

				while(threeHundredSecHasNotExpired())	{
					yield(tb3);
				}

				turnOffLED3();

				while(threeHundredSecHasNotExpired())	{
					yield(tb3);
				}

				count++;
			}
			count = 0;
			while(buttonStat())	{
				turnOffLED3();
				yield(tb3);
			}
		}
		yield(tb3);
	}
	endTask(x);
}
