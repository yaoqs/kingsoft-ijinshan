/********************************************************************
* CreatedOn: 2006-11-23   15:32
* FileName:  KXMLUtil.h
* CreatedBy: zhangrui <zhangrui@kingsoft.net>
* $LastChangedDate$
* $LastChangedRevision$
* $LastChangedBy$
* $HeadURL$
* Purpose:
*********************************************************************/

#ifndef __KXMLUtil_H_
#define __KXMLUtil_H_

#include "KXMLDataAccess.h"


//////////////////////////////////////////////////////////////////////////
//
// �˴�����Ҫ���ڽ�������������(�ڽ����Զ���)����XML���л�
// ��Ҫ�Ľӿ�����KXMLDataAccess�����KXMLDataAccess.h

//////////////////////////////////////////////////////////////////////////
// һ�����͵Ľṹ�����Ҫ֧��xml���ݽ��������ְ취
//
// 1,ʹ��KDX_XXX��
// 
//
// Example:
//
//class KTestPoint
//{
//public:
//    int m_x;
//    int m_y;
//};
//
//KDX_BEGIN(KTestPoint);
//    KDX_OBJ_EX("x", m_x, 0);
//    KDX_OBJ_NM("y", m_y);
//KDX_END();
//
//=== ���˵�� =========================================================
//
// �����������,KDX_BEGIN()�Ĳ���ָ����Ҫ���н�������
// "x"��"y"ָ����Ԫ�ص�����,���ԱXML�Ľ����
//
// m_x��m_y������һ����ֵ���ʽ,������XML���н��ж�/д����
//
// KDX_OBJ_EX()�ĵ�����������һ����ڶ���������������ͬ����ֵ���ʽ,
// ��ָ���˶�XMLʧ��ʱ,��Ӧ��Ա��ȱʡֵ
// EX����Extra
//
// KDX_OBJ_NM()û��ָ��ȱʡֵ�Ĳ���,����ʧ��ʱ,ֱ�ӷ���ʧ��
// NM����Normal
// ����Ҳ�������ΪNightmare,��XMl����Ǹ�Nightmare (n_n)
//
//======================================================================
//
//class KTestLine
//{
//public:
//    KTestPoint m_vertexBegin;
//    KTestPoint m_vertexEnd;
//};
//
//KTestPoint MakeDefault_KTestPoint()
//{
//    KTestPoint testPoint = {0, 0};
//    return testPoint;
//}
//
//KDX_BEGIN(KTestLine);
//    KDX_OBJ_EX("begin", m_vertexBegin,  MakeDefault_KTestPoint());
//    KDX_OBJ_EX("end",   m_vertexEnd,    MakeDefault_KTestPoint());
//KDX_END();
//
//
//=== ȱʡֵ�������� ===================================================
//
// �����ڽ�(Build in)����,���Ժ����׿���ָ��һ��������Ϊȱʡֵ
// ���Ƕ��ڽṹ��(struct)����(class),����������İ취
//
// �����������ָ����һ������������Ϊ���ʽ
// ���⻹����������ת��,���캯���Ȱ취
// ֻҪ�Ǻ͵ڶ�����������ͬ����ֵ���ʽ,��������������
//
// Ҫע�����,���ﲻ��ʹ����ʽ����ת��,������ȷ�����������ʽ������
//
//======================================================================
//
//
//


#endif//__KXMLUtil_H_
