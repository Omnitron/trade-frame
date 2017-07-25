/************************************************************************
 * Copyright(c) 2017, One Unified. All rights reserved.                 *
 * email: info@oneunified.net                                           *
 *                                                                      *
 * This file is provided as is WITHOUT ANY WARRANTY                     *
 *  without even the implied warranty of                                *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.                *
 *                                                                      *
 * This software may not be used nor distributed without proper license *
 * agreement.                                                           *
 *                                                                      *
 * See the file LICENSE.txt for redistribution information.             *
 ************************************************************************/
/* 
 * File:   NotebookOptionChains.cpp
 * Author: raymond@burkholder.net
 * 
 * Created on July 2, 2017, 8:16 PM
 */

#include <boost/lexical_cast.hpp>

#include "NotebookOptionChains.h"

namespace ou { // One Unified
namespace tf { // TradeFrame

NotebookOptionChains::NotebookOptionChains(): wxNotebook() {
  Init();
}

NotebookOptionChains::NotebookOptionChains( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style, const wxString& name )
: wxNotebook()
{
  Init();
  Create(parent, id, pos, size, style, name );
}

NotebookOptionChains::~NotebookOptionChains() {
}

void NotebookOptionChains::Init() {
}

bool NotebookOptionChains::Create( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style, const wxString& name ) {
  
  Init();
  
  wxNotebook::Create(parent, id, pos, size, style, name );
  
  CreateControls();

  return true;
}

void NotebookOptionChains::CreateControls() {    
  
  Bind( wxEVT_NOTEBOOK_PAGE_CHANGING, &NotebookOptionChains::OnPageChanging, this );
  Bind( wxEVT_NOTEBOOK_PAGE_CHANGED, &NotebookOptionChains::OnPageChanged, this );
  
  //Bind( wxEVT_CLOSE_WINDOW, &WinChartView::OnClose, this );  // not called for child windows
  Bind( wxEVT_DESTROY, &NotebookOptionChains::OnDestroy, this );
  
  //Bind( wxEVT_PAINT, &WinChartView::HandlePaint, this );
  //Bind( wxEVT_SIZE, &GridOptionDetails::HandleSize, this );
  
  //Bind( wxEVT_MOTION, &WinChartView::HandleMouse, this );
  //Bind( wxEVT_MOUSEWHEEL, &WinChartView::HandleMouseWheel, this );
  //Bind( wxEVT_ENTER_WINDOW, &WinChartView::HandleMouseEnter, this );  
  //Bind( wxEVT_LEAVE_WINDOW, &WinChartView::HandleMouseLeave, this );

  //Bind( EVENT_DRAW_CHART, &WinChartView::HandleGuiDrawChart, this );

  // this GuiRefresh initialization should come after all else
  //m_timerGuiRefresh.SetOwner( this );
  //Bind( wxEVT_TIMER, &GridOptionDetails::HandleGuiRefresh, this, m_timerGuiRefresh.GetId() );
  //m_timerGuiRefresh.Start( 250 );
  
  auto p = new GridOptionDetails( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxNO_BORDER, "a name" );
  AddPage( p, "page 1", true );

}

void NotebookOptionChains::SetName( const std::string& sName ) {
  
}

void NotebookOptionChains::Clear() {
  m_mapOptionExpiry.clear();
}

void NotebookOptionChains::Add( boost::gregorian::date date, double strike, ou::tf::OptionSide::enumOptionSide side, const std::string& sSymbol ) {
  
  mapOptionExpiry_t::iterator iterExpiry = m_mapOptionExpiry.find( date );
  if ( m_mapOptionExpiry.end() == iterExpiry ) {
    std::string sDate = boost::lexical_cast<std::string>( date.year() ) + "/";
    sDate += date.month() < 10 ? "0" : "" + boost::lexical_cast<std::string>( date.month() ) + "/";
    sDate += date.day() < 10 ? "0" : "" + boost::lexical_cast<std::string>( date.day() );
    // may need a sizer to go along with this
    auto* p = new GridOptionDetails( this, -1, wxDefaultPosition, wxDefaultSize, 0, sSymbol );
    size_t nPage( m_mapOptionExpiry.size() );
    InsertPage( nPage, p, sDate );
    iterExpiry = m_mapOptionExpiry.insert( 
      m_mapOptionExpiry.begin(), mapOptionExpiry_t::value_type( date, Tab( nPage, sDate, p ) ) );
  }
  
  mapStrike_t& mapStrike( iterExpiry->second.mapStrike ); // assumes single thread
  
  mapStrike_t::iterator iterStrike = mapStrike.find( strike );
  if ( mapStrike.end() == iterStrike ) {
    iterStrike = mapStrike.insert( mapStrike.begin(), mapStrike_t::value_type( strike, Row( mapStrike.size() ) ) );
  }
  switch ( side ) {
    case ou::tf::OptionSide::Call:
      assert( "" == iterStrike->second.sCall );
      iterStrike->second.sCall = sSymbol;
      break;
    case ou::tf::OptionSide::Put:
      assert( "" == iterStrike->second.sPut );
      iterStrike->second.sPut = sSymbol;
      break;
  }
  
  
}

// build grids on demand, or pre-build?
void NotebookOptionChains::OnPageChanging( wxBookCtrlEvent& event ) {
  event.Skip();
}

void NotebookOptionChains::OnPageChanged( wxBookCtrlEvent& event ) {
  event.Skip();
}

void NotebookOptionChains::OnDestroy( wxWindowDestroyEvent& event ) {
  
  DeleteAllPages();
  
  //m_timerGuiRefresh.Stop();
  //Unbind( wxEVT_TIMER, &WinChartView::HandleGuiRefresh, this, m_timerGuiRefresh.GetId() );
  
  Unbind( wxEVT_DESTROY, &NotebookOptionChains::OnDestroy, this );
  
  //Unbind( wxEVT_PAINT, &WinChartView::HandlePaint, this );
  //Unbind( wxEVT_SIZE, &GridOptionDetails::HandleSize, this );
  
  //Unbind( wxEVT_MOTION, &WinChartView::HandleMouse, this );
  //Unbind( wxEVT_MOUSEWHEEL, &WinChartView::HandleMouseWheel, this );
  //Unbind( wxEVT_ENTER_WINDOW, &WinChartView::HandleMouseEnter, this );  
  //Unbind( wxEVT_LEAVE_WINDOW, &WinChartView::HandleMouseLeave, this );

  event.Skip();  // auto followed by Destroy();
}

void NotebookOptionChains::Save( boost::archive::text_oarchive& oa) {
  //oa & m_splitter->GetSashPosition();
  //m_pTreeOps->Save<TreeItemRoot>( oa );
}

void NotebookOptionChains::Load( boost::archive::text_iarchive& ia) {
  //int pos;
  //ia & pos;
  //m_splitter->SetSashPosition( pos );
  //m_pTreeOps->Load<TreeItemRoot>( ia );
}
wxBitmap NotebookOptionChains::GetBitmapResource( const wxString& name ) {
    wxUnusedVar(name);
    return wxNullBitmap;
}

wxIcon NotebookOptionChains::GetIconResource( const wxString& name ) {
    wxUnusedVar(name);
    return wxNullIcon;
}

} // namespace tf
} // namespace ou