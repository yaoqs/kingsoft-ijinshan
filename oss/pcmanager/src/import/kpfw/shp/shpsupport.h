////////////////////////////////////////////////////////////////////////////////
//      
//      Kingsoft File for shp routines file
//      
//      File      : shpsupport.h
//      Comment   : simple html parser object base class
//					
//      Create at : 2008-09-04
//      Create by : chenguicheng
//      
////////////////////////////////////////////////////////////////////////////////

#pragma  once

#include "shpitem.h"
#include "shpbase.h"
#include <framework/kis_pathcfg.h>

#define NO_PROCESS			NULL


//////////////////////////////////
//��һ������󻭺���ʵ��(δ���)
//////////////////////////////////

//֧��win32 API ��Ԫ��
class shp_item_win32 : public shp_item
{
public:
	virtual ~shp_item_win32()
	{
	};

	BEGIN_KEY_MAP()
		//to add new attribute map( key map to member )
		BASE_CLASS_PROCESS(shp_item)
	END_KEY_MAP()

	virtual void draw_item( HDC hdc, CRect* parent_rect, CRect *left_rect ) = 0;

	virtual CRect* get_draw_rect() = 0;

	//������hit_test ���� false
	virtual LPCTSTR hit_test( HDC hdc, UINT umsg, int x, int y ) = 0;

};

typedef shp_tree_item< shp_item_win32 >		shp_dom_item;


//֧��agg��Ԫ��

class shp_item_agg : public shp_item
{
	virtual void draw_item() = 0;
};

//��� tree_item ����
//����ʹ�����淽�������µ�Ԫ��
/*
class shp_div_item :public shp_item_win32
{
	virtual void draw_item(HDC hdc)
	{
		return;
	}
};

typedef tree_item< shp_div_item >		shp_div_obj; //���������Ԫ�أ�����û�б仯
*/


//typedef shp_obj< ,div_item >  shp_div_obj; // ����һ���µ�divԪ��