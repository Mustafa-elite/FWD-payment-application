#include "Card.h"
#include <string.h>
EN_cardError_t getCardHolderName(ST_cardData_t* cardData)
{
	uint8_t bufferName[50]={0};
	printf("please enter the card holder name in 20-24 chars:");
	fgets(bufferName, 50, stdin);
	bufferName[strcspn(bufferName, "\n")] = 0;
	if (strlen(bufferName) < 20 || strlen(bufferName) > 24)
	{
		return WRONG_NAME;
	}
	else
	{
		strcpy_s(cardData->cardHolderName,25, bufferName);
		return CARD_OK;
	}
}
EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData)
{
	uint8_t bufferDate[20]={0};
	printf("please enter the card expiry date in this format (mm/yy):");
	fgets(bufferDate, 20, stdin);
	bufferDate[strcspn(bufferDate, "\n")]=0;
	if (strlen(bufferDate) != 5 ||bufferDate[2]!='/')
	{
		return WRONG_EXP_DATE;
	}
	else
	{
		if (bufferDate[0] < '0' || bufferDate[0]> '1' ||
			bufferDate[1] < '0' || bufferDate[1]> '9' ||
			bufferDate[3] < '0' || bufferDate[3]> '9' ||
			bufferDate[4] < '0' || bufferDate[4]> '9')
		{
			return WRONG_EXP_DATE;
		}
		else
		{
			if ((bufferDate[0] == '0' && bufferDate[1] == '0') ||
				(bufferDate[0] == '1' && bufferDate[1]  > '2')   )
			{
				return WRONG_EXP_DATE;

			}
			else
			{
				strcpy_s(cardData->cardExpirationDate, 6, bufferDate);
				return CARD_OK;
			}
		}
	}
}
EN_cardError_t getCardPAN(ST_cardData_t* cardData)
{
	char bufferPan[30];
	printf("Please enter your PAN: ");
	fgets(bufferPan, 30, stdin);
	int i;
	for (i = 0; i < 30; i++)
	{
		if (bufferPan[i] == '\0')
		{
			break;
		}
		else if (bufferPan[i] == '\n')
		{
			bufferPan[i] = 0;
			break;
		}
		else if(bufferPan[i] < '0' || bufferPan[i] > '9')
		{
			return WRONG_PAN;
		}
		else{}
	}
	if (i < 16 || i > 19)
	{
		return WRONG_PAN;
	}
	else
	{
		strcpy_s(cardData->primaryAccountNumber, 20, bufferPan);
		return CARD_OK;
	}
}