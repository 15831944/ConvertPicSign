#include "StdAfx.h"
#include "PubFunction.h"
namespace arxPub
{

AcDbObjectId PostToModelSpace(AcDbEntity *pEnt)
{
	assert(pEnt);//������������Ч��

	/*��õ�ǰͼ�����ݿ���*/
	AcDbBlockTable *pBlkTbl = NULL;
	acdbHostApplicationServices()->workingDatabase()->getBlockTable(pBlkTbl, AcDb::kForRead);

	/*���ģ�Ϳռ��Ӧ�Ŀ���¼*/
	AcDbBlockTableRecord *pBlkTblRcd = NULL;
	pBlkTbl->getAt(ACDB_MODEL_SPACE, pBlkTblRcd, AcDb::kForWrite);
	pBlkTbl->close();

	/*��ʵ����ӽ�����¼*/
	AcDbObjectId entId;
	Acad::ErrorStatus es = pBlkTblRcd->appendAcDbEntity(entId, pEnt);
	if(es != Acad::eOk)
	{
		pBlkTblRcd->close();
		delete pEnt;
		pEnt = NULL;
		return AcDbObjectId::kNull;
	}

	/*�ر�ʵ��Ϳ���¼*/
	pBlkTblRcd->close();
	pEnt->close();
	return entId;
}

char* ChangeCstringToCh(CString strIn)
{
	char* pBuffer = NULL;
#ifdef _UNICODE
	long lBufferSize;
	lBufferSize = WideCharToMultiByte(CP_ACP, 0, (LPCWSTR)(strIn), -1, NULL, 0, NULL, NULL);
	pBuffer = new char[lBufferSize + 1];
	memset(pBuffer,0,lBufferSize + 1);
	WideCharToMultiByte(CP_ACP, 0, (LPCWSTR)(strIn), -1,pBuffer, lBufferSize + 1, NULL, NULL);

#else
	pBuffer = new char[strIn.GetLength()+1];
	strcpy(pBuffer, strIn);
#endif
	return pBuffer;
}

}