///////////////////////////////////////////////////////////////
//
//	Filename: 	DrawWindowsStandardInterface.h
//	Creator:	lichenglin  <lichenglin@kingsoft.net>
//	Date:		2007-5-16  13:49
//	Comment:	�»�window��׼����Ԫ��
//
///////////////////////////////////////////////////////////////

#pragma once

#define CHECKBOX_WIDTH 13
enum ENUM_CHECKBOX_STATUS
{
	// CBS_NORMAL ��win7sdk��tmschema.h(583) : see declaration of 'CBS_NORMAL'��ͻ
    // one of following value:
    CBS_NORMAL_STATUS   = 0x0001,    // ��ͨ״̬
    CBS_SELECTED_STATUS = 0x0002,    // ѡ���޽���״̬
    CBS_FOCUS_STATUS    = 0x0003,    // ѡ���н���״̬
    CBS_DISABLED_STATUS = 0x0004,    // ��ֹ״̬

    // make combination with:
    CBS_CHECKED_STATUS  = 0x0100     // check״̬ 
};


#define TREE_FLAG_WIDTH  9
enum ENUM_FLAGBTN_STATUS
{
    TFS_NOCHILD    = 0,      // û���ӽ��
    TFS_RETRACTILE = 1,      // ����״̬ +
    TFS_EXPANDED   = 2       // չ��״̬ -
};


inline void DrawCheckBox( HDC hdc, int x, int y, UINT uStatus )
{
    ATLASSERT( hdc != NULL );
    CDCHandle dc( hdc );
    int nOldDC = dc.SaveDC();

    //---------------------------------------------
    // ѡ����ɫ

    COLORREF crFrame;   // �߿���ɫ
    COLORREF crInner;   // �ڲ���ɫ
    COLORREF crTick;    // ������ɫ

    if( uStatus & CBS_DISABLED_STATUS )
    {
        crFrame = 0xBBC8CA;
        crInner = 0xFFFFFF;
        crTick  = 0xBBC8CA;
    }
    else if( uStatus & CBS_NORMAL_STATUS )
    {
        crFrame = 0x80511C;
        crInner = 0xFDFDFD;
        crTick  = 0x21A121;
    }
    else if( uStatus & CBS_SELECTED_STATUS )
    {
        crFrame = 0x80511C;
        crInner = 0xFDFDFD;
        crTick  = 0x21A121;
    }
    else if( uStatus & CBS_FOCUS_STATUS )
    {
        crFrame = 0x80511C;
        crInner = 0xFDFDFD;
        crTick  = 0x21A121;
    }
    else
    {
        ATLASSERT( false ); // ���뻭ʲô״̬?
    }


    //---------------------------------------------
    // ����
    CPen   penFrame;
    CBrush brushInner;

    penFrame.CreatePen( PS_SOLID, 1, crFrame );
    brushInner.CreateSolidBrush( crInner );

    dc.SelectPen( penFrame );
    dc.SelectBrush( brushInner );


    dc.Rectangle( x, y, x + CHECKBOX_WIDTH, y + CHECKBOX_WIDTH );

    //---------------------------------------------
    // ����
    if( uStatus & CBS_CHECKED_STATUS ) 
    {
        CPen  penTick;
        penTick.CreatePen( PS_SOLID, 1, crTick );
        dc.SelectPen( penTick );


        for( int i = 3; i < 10; i++ )
        {
            dc.MoveTo( x + i, y + 3 + ((i < 6) ? i - 1 : (9 - i)));
            dc.LineTo( x + i, y + 3 + ((i < 6) ? i + 2 : (12 - i)));
        }
    }


    dc.RestoreDC( nOldDC );
}








////////////////////////////////////////////////////////////////////////////////
//
//  �� ���� ( ÿһ���ؿ�һ��, �ݲ�֧��б�� )
//
////////////////////////////////////////////////////////////////////////////////
inline void DrawDotLine( HDC hdc, POINT ptBegin, POINT ptEnd, COLORREF crColor )
{
    ATLASSERT( ptEnd.x - ptBegin.x == 0 || ptEnd.y - ptBegin.y == 0 ); // ����б��

    if( ptBegin.x > ptEnd.x || ptBegin.y > ptEnd.y )
    {
        POINT pt = ptBegin;
        ptBegin  = ptEnd;
        ptEnd    = pt;
    }

    for( int x = ptBegin.x; x <= ptEnd.x; x++ )
    {
        if( x & 1 )
        {
            ::SetPixel( hdc, x, ptBegin.y, crColor );
        }
    }

    for( int y = ptBegin.y; y <= ptEnd.y; y++ )
    {
        if(  y & 1 )
        {
            ::SetPixel( hdc, ptBegin.x, y, crColor );
        }
    }
}


////////////////////////////////////////////////////////////////////////////////
//
//  �� �������߱߿�
//
////////////////////////////////////////////////////////////////////////////////
inline void DrawDotRectFrame( HDC hdc, const RECT& rect, COLORREF crLine )
{
    CPoint ptTopLeft( rect.left, rect.top );
    CPoint ptTopRight( rect.right - 1, rect.top );
    CPoint ptBottomLeft( rect.left, rect.bottom - 1 );
    CPoint ptBottomRight( rect.right - 1, rect.bottom - 1 );

    DrawDotLine( hdc, ptTopLeft,    ptTopRight,    crLine );
    DrawDotLine( hdc, ptTopRight,   ptBottomRight, crLine );
    DrawDotLine( hdc, ptBottomLeft, ptBottomRight, crLine );
    DrawDotLine( hdc, ptTopLeft,    ptBottomLeft,  crLine );
}


/**
* @brief   �����ؼ�ǰ��ʾչ��/�����С���
* @param   [in]  hdc,    Ŀ��DC
* @param   [in]  x, y    ������Ͻ������dc��λ��
* @param   [in]  nStatus ���״̬, ������ֵ
* @return  
* @remark  
*/
inline void DrawTreeExpandFlag( HDC hdc, int x, int y, int nStatus )
{
    CDCHandle dc( hdc );

    const COLORREF crFrame = ::GetSysColor( COLOR_BTNSHADOW );
    const COLORREF crFlag  = ::GetSysColor( COLOR_BTNTEXT );
    const int nBtnWidth  = TREE_FLAG_WIDTH;
    const int nFlagWidth = TREE_FLAG_WIDTH * 3 / 5;

    if( nStatus == TFS_NOCHILD )
    {
        return;
    }

    //-------------------------------------
    // ����
    {
        int nSavedDC = dc.SaveDC();

        CPen penFrame;
        penFrame.CreatePen( PS_SOLID, 1, crFrame );

        dc.SelectPen( penFrame );
        dc.SelectStockBrush( WHITE_BRUSH );
        dc.Rectangle( x, y, x + nBtnWidth, y + nBtnWidth );

        dc.RestoreDC( nSavedDC );
    }

    //-------------------------------------
    // ���Ӽ���
    {
        int nSavedDC = dc.SaveDC();

        CPen penFlag;
        penFlag.CreatePen( PS_SOLID, 1, crFlag );

        dc.SelectPen( penFlag );

        // -
        dc.MoveTo( x + ( nBtnWidth - nFlagWidth) / 2, y + nBtnWidth / 2, NULL );
        dc.LineTo( x + ( nBtnWidth - nFlagWidth) / 2 + nFlagWidth, y + nBtnWidth / 2 );

        // |
        if( nStatus == TFS_RETRACTILE )
        {
            dc.MoveTo( x + nBtnWidth / 2, y + ( nBtnWidth - nFlagWidth) / 2, NULL );
            dc.LineTo( x + nBtnWidth / 2, y + ( nBtnWidth - nFlagWidth) / 2 + nFlagWidth );
        }

        dc.RestoreDC( nSavedDC );
    }

}