//原文地址: http://www.tuicool.com/articles/JFjqIvF


struct UartInfo
{
  DWORD UartNum;
  WCHAR UartName[20];
};

//获取串口列表
BOOL EnumComs(struct UartInfo **UartCom, LPDWORD UartComNumber, CnuprogDlg *pMainDlg)
{
  //LPCTSTR 即const char * 

  *UartComNumber = 0;
  HKEY hNewKey;
  LONG lResult=RegOpenKeyEx( HKEY_LOCAL_MACHINE, L"HARDWARE\\DEVICEMAP\\SERIALCOMM", 0, KEY_ALL_ACCESS, &hNewKey);   
  if(lResult != ERROR_SUCCESS)  
  {   
    pMainDlg->AddToInfOut(_T("打开COM注册表失败！！！"),1,1);
    return FALSE;   
  }
  else
  {
    pMainDlg->AddToInfOut(_T("打开COM注册表成功！！！"),1,1);
  }

  //DWORD即unsigned long
  DWORD ValuesNumber;
  DWORD MaxValueNameLen;
  DWORD MaxValueLen;
  CString str;
  //检索指定的子键下有多少个值项
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
     //pMainDlg->AddToInfOut(_T("检索连接在PC上的串口数量失败！！！"),1,1);
     return FALSE;
   }
   else
   {
    // str.Format(_T("连接在PC上的串口数量是：%ld"), ValuesNumber);
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

   //LPTSTR 即 char *, LPBYTE即 char *
   //检索每个值项，获取值名，数据类型，数据
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
       //pMainDlg->AddToInfOut(_T("检索串口完毕！！！"),1,1);
     }
     else
     {
       DWORD dw = GetLastError();
      // str.Format(_T("检索串口出错: 0x%08x"), dw);
      // pMainDlg->AddToInfOut(str,1,1);
       return FALSE;
     }
   }

   *UartComNumber = uartindex;

   return TRUE;
}

//以下内容为在主函数中调用时使用；
/* DWORD UartComNumber = 0;
  struct UartInfo *pUartCom;
  BOOL bResult;
  bResult = EnumComs(&pUartCom, &UartComNumber, pMainDlg);
  DWORD index;

  if(bResult)
  {
    pMainDlg->AddToInfOut(_T("获取串口列表成功"),1,1);
  }
  else
  {
    pMainDlg->AddToInfOut(_T("获取串口列表失败"),1,1);
  }

  for( index= 0;index < UartComNumber; index++) 
  {  
    pMainDlg->m_ComboBox.AddString(pUartCom[index].UartName);
  } */





