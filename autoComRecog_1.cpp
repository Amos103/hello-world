//ԭ�ĵ�ַ: http://www.tuicool.com/articles/JFjqIvF


struct UartInfo
{
  DWORD UartNum;
  WCHAR UartName[20];
};

//��ȡ�����б�
BOOL EnumComs(struct UartInfo **UartCom, LPDWORD UartComNumber, CnuprogDlg *pMainDlg)
{
  //LPCTSTR ��const char * 

  *UartComNumber = 0;
  HKEY hNewKey;
  LONG lResult=RegOpenKeyEx( HKEY_LOCAL_MACHINE, L"HARDWARE\\DEVICEMAP\\SERIALCOMM", 0, KEY_ALL_ACCESS, &hNewKey);   
  if(lResult != ERROR_SUCCESS)  
  {   
    pMainDlg->AddToInfOut(_T("��COMע���ʧ�ܣ�����"),1,1);
    return FALSE;   
  }
  else
  {
    pMainDlg->AddToInfOut(_T("��COMע���ɹ�������"),1,1);
  }

  //DWORD��unsigned long
  DWORD ValuesNumber;
  DWORD MaxValueNameLen;
  DWORD MaxValueLen;
  CString str;
  //����ָ�����Ӽ����ж��ٸ�ֵ��
   lResult = RegQueryInfoKey(
                  hNewKey,
                  NULL,
                  NULL,
                  NULL,
                  NULL,
                  NULL,
                  NULL,
                  &ValuesNumber,
                  &MaxValueNameLen,
                  &MaxValueLen,
                  NULL,
                  NULL
                );
   if(lResult != ERROR_SUCCESS)
   {
     RegCloseKey(hNewKey);
     //pMainDlg->AddToInfOut(_T("����������PC�ϵĴ�������ʧ�ܣ�����"),1,1);
     return FALSE;
   }
   else
   {
    // str.Format(_T("������PC�ϵĴ��������ǣ�%ld"), ValuesNumber);
    // pMainDlg->AddToInfOut(str,1,1);
    *UartCom =(struct UartInfo *)malloc( ValuesNumber * sizeof(struct UartInfo)); 
   }

   DWORD index;
   DWORD uartindex = 0;
   //CHAR  ValueName[MAX_VALUE_NAME]; 
   WCHAR  ValueName[100]; 
   //DWORD ValueNameSize = MAX_VALUE_NAME;
   DWORD ValueNameSize;
   DWORD DataType;
   BYTE DataBuffer[100];
   DWORD DataLen = 100;

   //LPTSTR �� char *, LPBYTE�� char *
   //����ÿ��ֵ���ȡֵ�����������ͣ�����
   for(index = 0; index < ValuesNumber; index++)
   {
     memset(ValueName, 0, sizeof(ValueName));
     memset(DataBuffer, 0, sizeof(DataBuffer));
     ValueNameSize = 100;
     DataLen = 100;
     lResult = RegEnumValue(hNewKey,index,ValueName,&ValueNameSize,NULL, &DataType, DataBuffer, &DataLen);
     if (lResult == ERROR_SUCCESS ) 
     {
       switch(DataType)
       {
         case REG_NONE:			 // No value type				(0)
           break;
         case REG_SZ:			//Unicode nul terminated string (1)
          break;
         case REG_EXPAND_SZ:	// Unicode nul terminated string (2)
           break;
         case REG_BINARY:		// Free form binary				 (3)
           break;
         case REG_DWORD:		// 32-bit number				(4)
           break;
         case REG_MULTI_SZ:		 // Multiple Unicode strings	(7)
           break;
         default:
           break;
       }
       memcpy((*UartCom)[uartindex].UartName, DataBuffer, DataLen);
       (*UartCom)[uartindex].UartNum = ValuesNumber;
       uartindex++;
     }
     else if(lResult == ERROR_NO_MORE_ITEMS)
     {
       //pMainDlg->AddToInfOut(_T("����������ϣ�����"),1,1);
     }
     else
     {
       DWORD dw = GetLastError();
      // str.Format(_T("�������ڳ���: 0x%08x"), dw);
      // pMainDlg->AddToInfOut(str,1,1);
       return FALSE;
     }
   }

   *UartComNumber = uartindex;

   return TRUE;
}

//��������Ϊ���������е���ʱʹ�ã�
/* DWORD UartComNumber = 0;
  struct UartInfo *pUartCom;
  BOOL bResult;
  bResult = EnumComs(&pUartCom, &UartComNumber, pMainDlg);
  DWORD index;

  if(bResult)
  {
    pMainDlg->AddToInfOut(_T("��ȡ�����б�ɹ�"),1,1);
  }
  else
  {
    pMainDlg->AddToInfOut(_T("��ȡ�����б�ʧ��"),1,1);
  }

  for( index= 0;index < UartComNumber; index++) 
  {  
    pMainDlg->m_ComboBox.AddString(pUartCom[index].UartName);
  } */





