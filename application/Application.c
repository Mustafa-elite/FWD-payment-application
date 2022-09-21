#include "Application.h"

void appStart(void)
{
	/**********************************************************************************/
	/*******************************CARD MODULE****************************************/
	/**********************************************************************************/
	ST_cardData_t card1;
	ST_terminalData_t terminal1;
	EN_cardError_t cardErr = CARD_OK;
	cardErr = getCardHolderName(&card1);
	if (cardErr != CARD_OK)
	{
		printf("wrong name input!\n");
		return;
	}
	else
	{
		cardErr = getCardExpiryDate(&card1);
		if (cardErr != CARD_OK)
		{
			printf("wrong date input!\n");
			return;
		}
		else
		{
			cardErr = getCardPAN(&card1);
			if (cardErr != CARD_OK)
			{
				printf("wrong PAN number input!\n");
				return;
			}
			else {}
		}
	}
	/**********************************************************************************/
	/*******************************Terminal MODULE************************************/
	/**********************************************************************************/
	EN_terminalError_t termErr = OK;
	termErr = getTransactionDate(&terminal1);
	if (termErr != OK)
	{
		printf("INVALID DATE!\n");
		return;
	}
	else
	{
		termErr = isCardExpired(&card1, &terminal1);
		if (termErr != OK)
		{
			printf("CARD EXPIRED!!!\n");
			return;
		}
		else
		{
			termErr = setMaxAmount(&terminal1);
			if (termErr != OK)
			{
				printf("INVALID NUMBER!\n");
				return;
			}
			else
			{
				termErr = getTransactionAmount(&terminal1);
				if (termErr != OK)
				{
					printf("INVALID AMMOUNT\n");
					return;
				}
				else
				{
					termErr = isBelowMaxAmount(&terminal1);
					if (termErr != OK)
					{
						printf("INSUFFICIENT AMMOUNT");
						return;
					}
					else {}
				}
			}
		}
	}
	/**********************************************************************************/
	/*********************************SERVER MODULE************************************/
	/**********************************************************************************/
	EN_serverError_t transactionState;
	ST_transaction_t transaction;
	transaction.cardHolderData = card1;
	transaction.terminalData = terminal1;
	EN_serverError_t isValid;
	ST_accountsDB_t* accRefrence;
	EN_accountState_t isAmAvailable;
	isValid = isValidAccount(&(transaction.cardHolderData), &accRefrence);
	if (isValid == ACCOUNT_NOT_FOUND)
	{
		printf("account not found!\n");
	}
	else
	{
		isAmAvailable = isAmountAvailable(&(transaction.terminalData), accRefrence);
		if (accRefrence->state == BLOCKED)
		{
			printf("Blocked account!!\n");
		}
		else if (isAmAvailable == LOW_BALANCE)
		{
			printf("LOW BALANCE!!\n");
		}
		else {}
	}


	transactionState = saveTransaction(&transaction);
	if (transactionState == SAVING_FAILED)
	{
		printf("saving failed\n");
	}
	else if (transactionState == SERVER_OK)
	{
		printf("transaction saved sucessfully\ncongratulation the project came to its end\n");
	}
	else
	{
		printf("test unsucessfull");
	}
}