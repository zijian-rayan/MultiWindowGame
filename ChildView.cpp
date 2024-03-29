
// ChildView.cpp : implémentation de la classe CChildView
//

#include "stdafx.h"
#include "MultiEchiquier.h"
#include "ChildView.h"
//#include "Param.h"
#include "MainFrm.h"
#include<gdiplus.h>
#include<atlimage.h>
#pragma comment(lib,"gdiplus.lib")
//#define ULONG_PTR ULONG
using namespace Gdiplus;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

CChildView::CChildView():loaded (false) {}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
  ON_COMMAND(ID_PAIRE1, &CChildView::OnPaire1)
  ON_UPDATE_COMMAND_UI(ID_PAIRE1, &CChildView::OnUpdatePaire1)
  ON_COMMAND(ID_PAIRE2, &CChildView::OnPaire2)
  ON_UPDATE_COMMAND_UI(ID_PAIRE2, &CChildView::OnUpdatePaire2)
  ON_COMMAND(ID_PAIRE3, &CChildView::OnPaire3)
  ON_UPDATE_COMMAND_UI(ID_PAIRE3, &CChildView::OnUpdatePaire3)
  ON_COMMAND(ID_TAILLE_10X10, &CChildView::OnTaille10x10)
  ON_UPDATE_COMMAND_UI(ID_TAILLE_10X10, &CChildView::OnUpdateTaille10x10)
  ON_COMMAND(ID_TAILLE_12X12, &CChildView::OnTaille12x12)
  ON_UPDATE_COMMAND_UI(ID_TAILLE_12X12, &CChildView::OnUpdateTaille12x12)
  ON_COMMAND(ID_TAILLE_4X4, &CChildView::OnTaille4x4)
  ON_UPDATE_COMMAND_UI(ID_TAILLE_4X4, &CChildView::OnUpdateTaille4x4)
  ON_COMMAND(ID_TAILLE_6X6, &CChildView::OnTaille6x6)
  ON_UPDATE_COMMAND_UI(ID_TAILLE_6X6, &CChildView::OnUpdateTaille6x6)
  ON_COMMAND(ID_TAILLE_8X8, &CChildView::OnTaille8x8)
  ON_UPDATE_COMMAND_UI(ID_TAILLE_8X8, &CChildView::OnUpdateTaille8x8)
  ON_COMMAND(ID_VISIBLE, &CChildView::OnVisible)
  ON_UPDATE_COMMAND_UI(ID_VISIBLE, &CChildView::OnUpdateVisible)
  ON_COMMAND(ID_AFFICHAGE_ZOOMIN, &CChildView::OnAffichageZoomin)
  ON_UPDATE_COMMAND_UI(ID_AFFICHAGE_ZOOMIN, &CChildView::OnUpdateAffichageZoomin)
  ON_COMMAND(ID_AFFICHAGE_ZOOMOUT, &CChildView::OnAffichageZoomout)
  ON_UPDATE_COMMAND_UI(ID_AFFICHAGE_ZOOMOUT, &CChildView::OnUpdateAffichageZoomout)
  ON_COMMAND(ID_COULEUR_CASESPAIRES, &CChildView::OnCouleurCasespaires)
  ON_COMMAND(ID_COULEUR_CASESIMPAIRES, &CChildView::OnCouleurCasesimpaires)
//  ON_COMMAND(ID_FICHIER_, &CChildView::OnFichier)
  ON_COMMAND(ID_FICHIER_SAVEIMG, &CChildView::OnFichierSaveimg)
  ON_COMMAND(ID_PARAMS, &CChildView::OnParams)
  ON_WM_MOUSEMOVE()
  ON_WM_RBUTTONDOWN()
  ON_COMMAND(ID_NOIRE, &CChildView::OnNoire)
  ON_COMMAND(ID_BLANCHE, &CChildView::OnBlanche)
END_MESSAGE_MAP()

COLORREF CChildView::tclr[3][2]={{0x303030,0x0000FF},{0x303030,0x00FF00},{0x00FF00,0x00FFFF}};
int CChildView::zoom=0;

int valx=0,valy=0;
// gestionnaires de messages pour CChildView

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(NULL, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), NULL);
  
	return TRUE;
}

void CChildView::OnPaint() 
{
  CPaintDC dc(this); // contexte de p閞iph閞ique pour la peinture
  if(!loaded)
  {
		  dc.SetMapMode(MM_ISOTROPIC);
		  dc.SetWindowExt((zoom>0?1:1-zoom),(zoom>0?1:1-zoom));
		  dc.SetViewportExt((zoom>0?zoom+1:1),(zoom>0?zoom+1:1));
		 
		  Show (dc);

		  for(WORD ii=0;ii<ny;ii++)
		  {
			  for(WORD jj=0;jj<nx;jj++)
			  {
					  if(cas[ii][jj]==1)
					  {
						CPen BlackPen(PS_SOLID,5,RGB(0,0,0));
						CPen *pOldPen = dc.SelectObject(&BlackPen);
						CBrush *pbrush = CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH));
						dc.SelectObject(pbrush);
						//dc.SelectObject(ppold);
						//dc.Arc(CRect(valx*cx,valy*cy,valx*cx+cx,valy*cy+cy),CPoint(mpoint.x,mpoint.y),CPoint(mpoint.x,mpoint.y));
						dc.Ellipse(ii*cx+2.5,jj*cy+2.5,(ii+1)*cx-2.5,(jj+1)*cy-2.5);
						dc.SelectObject(pOldPen);
						BlackPen.DeleteObject();
					  }
					  if(cas[ii][jj]==2)
					  {
						CPen WhitePen(PS_SOLID,5,RGB(255,255,255));
						CPen *pOldPen = dc.SelectObject(&WhitePen);
						//dc.Arc(CRect(valx*cx,valy*cy,valx*cx+cx,valy*cy+cy),CPoint(mpoint.x,mpoint.y),CPoint(mpoint.x,mpoint.y));
						//dc.SelectObject(pOldPen);
						//WhitePen.DeleteObject();
						//CPen p(PS_SOLID, 3, RGB(255,255,255));
						//CPen* ppold=dc.SelectObject(&p);
						CBrush *pbrush = CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH));
						dc.SelectObject(pbrush);
						//dc.SelectObject(ppold);
						//dc.Arc(CRect(valx*cx,valy*cy,valx*cx+cx,valy*cy+cy),CPoint(mpoint.x,mpoint.y),CPoint(mpoint.x,mpoint.y));
						dc.Ellipse(ii*cx+2.5,jj*cy+2.5,(ii+1)*cx-2.5,(jj+1)*cy-2.5);
						dc.SelectObject(pOldPen);
						WhitePen.DeleteObject();
					  }
			  }

		  }
  }
  if(loaded)
	  {
		  CDC mdc; // memory DC
		  mdc.CreateCompatibleDC(&dc);
		  CBitmap* pOld = mdc.SelectObject(&cbmp);
		  dc.BitBlt(0,0,bmp.bmWidth,bmp.bmHeight,&mdc,0,0,SRCCOPY);
		  mdc.SelectObject(pOld);
	  }

	// TODO : ajoutez ici le code de votre gestionnaire de messages
	// Ne pas appeler CWnd::OnPaint() pour la peinture des messages
}

bool CChildView::LoadImage(CString &fname)
{
  cbmp.Attach(::LoadImage(0,fname,IMAGE_BITMAP, 0, 0,
    LR_LOADFROMFILE | LR_CREATEDIBSECTION | LR_DEFAULTSIZE));
  cbmp.GetBitmap(&bmp);
  loaded=true;
  GetParent()->SendMessage(WM_SETTEXT,0,(LPARAM)((LPCTSTR)fname));
  Invalidate();
  return true;
}


void CChildView::OnPaire1()
{
  c2=tclr[0][0];c1=tclr[0][1];ct=0xFFFFFF;Invalidate();
  // TODO : ajoutez ici le code de votre gestionnaire de commande
}

void CChildView::OnUpdatePaire1(CCmdUI *pCmdUI)
{
  pCmdUI->SetCheck(c2==tclr[0][0]&&c1==tclr[0][1]);
  // TODO : ajoutez ici le code du gestionnaire d'interface utilisateur de mise ?jour des commandes
}

void CChildView::OnPaire2()
{
  c1=tclr[1][0];c2=tclr[1][1];ct=0x5050FF;Invalidate();
  // TODO : ajoutez ici le code de votre gestionnaire de commande
}

void CChildView::OnUpdatePaire2(CCmdUI *pCmdUI)
{
  pCmdUI->SetCheck(c1==tclr[1][0]&&c2==tclr[1][1]);
  // TODO : ajoutez ici le code du gestionnaire d'interface utilisateur de mise ?jour des commandes
}

void CChildView::OnPaire3()
{
  c1=tclr[2][0];c2=tclr[2][1];ct=0x5050FF;Invalidate();
  // TODO : ajoutez ici le code de votre gestionnaire de commande
}

void CChildView::OnUpdatePaire3(CCmdUI *pCmdUI)
{
  pCmdUI->SetCheck(c1==tclr[2][0]&&c2==tclr[2][1]);
  // TODO : ajoutez ici le code du gestionnaire d'interface utilisateur de mise ?jour des commandes
}

void CChildView::OnTaille10x10()
{
  nx=ny=10;Invalidate();
  // TODO : ajoutez ici le code de votre gestionnaire de commande
}

void CChildView::OnUpdateTaille10x10(CCmdUI *pCmdUI)
{
  pCmdUI->Enable(nx!=10||ny!=10);
  // TODO : ajoutez ici le code du gestionnaire d'interface utilisateur de mise ?jour des commandes
}

void CChildView::OnTaille12x12()
{
  nx=ny=12;Invalidate();
  // TODO : ajoutez ici le code de votre gestionnaire de commande
}

void CChildView::OnUpdateTaille12x12(CCmdUI *pCmdUI)
{
  
  pCmdUI->Enable(nx!=12||ny!=12);// TODO : ajoutez ici le code du gestionnaire d'interface utilisateur de mise ?jour des commandes
}

void CChildView::OnTaille4x4()
{
  nx=ny=4;Invalidate();
  // TODO : ajoutez ici le code de votre gestionnaire de commande
}

void CChildView::OnUpdateTaille4x4(CCmdUI *pCmdUI)
{
  pCmdUI->Enable(nx!=4||ny!=4);
  // TODO : ajoutez ici le code du gestionnaire d'interface utilisateur de mise ?jour des commandes
}

void CChildView::OnTaille6x6()
{
  nx=ny=6;Invalidate();
  // TODO : ajoutez ici le code de votre gestionnaire de commande
}

void CChildView::OnUpdateTaille6x6(CCmdUI *pCmdUI)
{
  
  pCmdUI->Enable(nx!=6||ny!=6);// TODO : ajoutez ici le code du gestionnaire d'interface utilisateur de mise ?jour des commandes
}

void CChildView::OnTaille8x8()
{
  nx=ny=8;Invalidate();
  // TODO : ajoutez ici le code de votre gestionnaire de commande
}

void CChildView::OnUpdateTaille8x8(CCmdUI *pCmdUI)
{
  
  pCmdUI->Enable(nx!=8||ny!=8);// TODO : ajoutez ici le code du gestionnaire d'interface utilisateur de mise ?jour des commandes
}

void CChildView::OnVisible()
{
  show=!show;Invalidate();
  // TODO : ajoutez ici le code de votre gestionnaire de commande
}

void CChildView::OnUpdateVisible(CCmdUI *pCmdUI)
{
  
  // TODO : ajoutez ici le code du gestionnaire d'interface utilisateur de mise ?jour des commandes
}

void CChildView::OnAffichageZoomin()
{
  if(zoom>-4)
    zoom--;Invalidate();
  // TODO : ajoutez ici le code de votre gestionnaire de commande
}

void CChildView::OnUpdateAffichageZoomin(CCmdUI *pCmdUI)
{
	
	pCmdUI->Enable(zoom>-3);
  // TODO : ajoutez ici le code du gestionnaire d'interface utilisateur de mise ?jour des commandes
}

void CChildView::OnAffichageZoomout()
{
  // TODO : ajoutez ici le code de votre gestionnaire de commande
  if(zoom<4)
    zoom++;Invalidate();
}

void CChildView::OnUpdateAffichageZoomout(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(zoom<3);
  // TODO : ajoutez ici le code du gestionnaire d'interface utilisateur de mise ?jour des commandes
}

void CChildView::OnCouleurCasespaires()
{
  CColorDialog dlg(c1);
  if(dlg.DoModal()!=IDOK) return;
  c1=dlg.GetColor();
  Invalidate();
  // TODO : ajoutez ici le code de votre gestionnaire de commande
}

void CChildView::OnCouleurCasesimpaires()
{
   CColorDialog dlg(c2);
  if(dlg.DoModal()!=IDOK) return;
  c2=dlg.GetColor();
  Invalidate();
  // TODO : ajoutez ici le code de votre gestionnaire de commande
}

void CChildView::OnFichier()
{
	CDC *pDC = GetWindowDC();  //GDI+
	CDC memDC;
	memDC.CreateCompatibleDC(pDC);
	CRect rt;
	GetWindowRect(&rt);
	CBitmap Bmp;
	Bmp.CreateCompatibleBitmap(pDC,rt.Width(),rt.Height());
	CBitmap *pBmpPrev = (CBitmap*)memDC.SelectObject(&Bmp) ;
	memDC.BitBlt(0, 0, rt.Width(), rt.Height(), pDC, 0, 0, SRCCOPY);
	CImage image;
	image.Attach((HBITMAP)Bmp.m_hObject);
	image.Save(L"image.bmp");
}

void CChildView::OnFichierSaveimg()
{
	CMetaFileDC a;
	a.CreateEnhanced(NULL,_T("Figure.emf"),NULL,NULL);
	Show(a);
	a.CloseEnhanced();
}
void CChildView::OnParams()
{
  /*CParam dlg(this);
  dlg.m_nx=(BYTE)nx;dlg.m_ny=(BYTE)ny;
  for(dlg.m_paire=2;dlg.m_paire>=0;dlg.m_paire--)
    if(c1==tclr[dlg.m_paire][0]&&c2==tclr[dlg.m_paire][1]) break;
  if(dlg.DoModal()!=IDOK)return;
  nx=dlg.m_nx;ny=dlg.m_ny;
  if(dlg.m_paire!=-1){c1=tclr[dlg.m_paire][0];c2=tclr[dlg.m_paire][1];}
  Invalidate();*/
  // TODO : ajoutez ici le code de votre gestionnaire de commande
}


  void CChildView::OnMouseMove(UINT nFlags, CPoint point)
  {
    // TODO : ajoutez ici le code de votre gestionnaire de messages et/ou les paramètres par défaut des appels
    //CString msg;
    //msg.Format (_T("La position dans la fenêtre (%ld,%ld)"),point.x,point.y);
    //((CMainFrame*)(theApp.m_pMainWnd))-> m_wndStatusBar.SetWindowText(msg);
    //((CMainFrame*)(GetParent()))-> m_wndStatusBar.SetWindowText(msg);
    __super::OnMouseMove(nFlags, point);
  }

  void CChildView::OnRButtonDown(UINT nFlags, CPoint point)
  {
		CMenu menu;
		CRect rect_ctr;
		this->GetWindowRect(&rect_ctr);
		menu.LoadMenuW(IDR_MENU1);
		CMenu *pPopup=menu.GetSubMenu(0);
		pPopup->TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON,point.x+rect_ctr.left,point.y+rect_ctr.top,this);
		mpoint = point;
		
		__super::OnRButtonDown(nFlags, point);
  }

  void CChildView::OnNoire()
  {
	  valx = mpoint.x/cx/(zoom+1);valy = mpoint.y/cy/(zoom+1);
	  if(mpoint.x/(zoom+1)>cx*nx||mpoint.y/(zoom+1)>cy*ny)
			MessageBox(_T("Ne peut pas jouer en dehors d'echiquier"));
	  else
	  {
		  if(cas[valx][valy]!=0)
				MessageBox(_T("Il y a déjà une pièce ici."));
		  else
		  {
				cas[valx][valy]=1;
		  }
	  }
	  Invalidate();
	  // TODO: 在此添加命令处理程序代码
  }

  void CChildView::OnBlanche()
  {
  	  valx = mpoint.x/cx/(zoom+1);valy = mpoint.y/cy/(zoom+1);
	  if(mpoint.x/(zoom+1)>cx*nx||mpoint.y/(zoom+1)>cy*ny)
		  MessageBox(_T("Ne peut pas jouer en dehors d'echiquier"));
	  else
	  {
		  if(cas[valx][valy]!=0)
				MessageBox(_T("Il y a déjà une pièce ici."));
		  else
		  {
				cas[valx][valy]=2;
		  }
	  }
	  Invalidate();
  }
