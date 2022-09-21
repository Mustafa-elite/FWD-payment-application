#include "Terminal.h"


EN_terminalError_t getTransactionDate(ST_terminalData_t* termData)
{
	uint8_t bufferTransDate[15] = { 0 }, i = 0;
	sint8_t monthBuffer = 0, yearBuffer = 0, dayBuffer = 0;
	printf("please enter the transaction date(DD/MM/YYYY):");
	fgets(bufferTransDate, 15, stdin);
	bufferTransDate[strcspn(bufferTransDate, "\n")] = 0;
	if ((strlen(bufferTransDate) != 10) ||bufferTransDate[2]!='/' || bufferTransDate[5] != '/')
	{
		return WRONG_DATE;
	}
	else
	{
		dayBuffer = (bufferTransDate[1] - 48) + (bufferTransDate[0] - 48) * 10;
		monthBuffer = (bufferTransDate[4] - 48) + (bufferTransDate[3] - 48) * 10;
		if (dayBuffer < 1 || dayBuffer > 31 || monthBuffer < 1 || monthBuffer > 12 || bufferTransDate[6] == 0)
		{
			return WRONG_DATE;
		}
		else
		{
			strcpy_s(termData->transactionDate,11, bufferTransDate);
			return OK;
		}
	}
}
EN_terminalError_t isCardExpired(ST_cardData_t* cardData, ST_terminalData_t* termData)
{
	uint8_t cardMonthExp = 0, cardYearExp=0,transMonth=0,transYear=0;
	cardMonthExp = (cardData->cardExpirationDate[1] - 48) + (cardData->cardExpirationDate[0] - 48) * 10;
	cardYearExp = (cardData->cardExpirationDate[4] - 48) + (cardData->cardExpirationDate[3] - 48) * 10;
	transMonth = (termData->transactionDate[4] - 48) + (termData->transactionDate[3] - 48) * 10;
	transYear = (termData->transactionDate[9] - 48) + (termData->transactionDate[8] - 48) * 10;
	if (cardYearExp < transYear)
	{
		return EXPIRED_CARD;
	}
	else
	{
		if ((cardYearExp == transYear) &&(cardMonthExp < transMonth))
		{
			return EXPIRED_CARD;
		}
		else
		{
			return OK;
		}
	}
}
EN_terminalError_t getTransactionAmount(ST_terminalData_t* termData)
{
	f32 transAmmount = 0;
	printf("please enter the ammount of transaction:");
	scanf_s("%f", &transAmmount);
	if (transAmmount <= 0)
	{
		return INVALID_AMOUNT;
	}
	else
	{
		termData->transAmount = transAmmount;
		return OK;
	}
}
EN_terminalError_t setMaxAmount(ST_terminalData_t* termData)
{
	f32 maxAmm = 0;
	printf("please enter the max ammount:");
	scanf_s("%f", &maxAmm);
	if (maxAmm <= 0)
	{
		return INVALID_MAX_AMOUNT;
	}
	else
	{
		termData->maxTransAmount = maxAmm;
		return OK;
	}
}
EN_terminalError_t isBelowMaxAmount(ST_terminalData_t* termData)
{
	if (termData->transAmount > termData->maxTransAmount)
	{
		return EXCEED_MAX_AMOUNT;
	}
	else
	{
		return OK;
	}
}