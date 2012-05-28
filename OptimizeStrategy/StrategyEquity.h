/************************************************************************
 * Copyright(c) 2012, One Unified. All rights reserved.                 *
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

#pragma once

#include <boost/date_time/posix_time/posix_time.hpp>

#include <TFSimulation/SimulationProvider.h>
#include <TFTrading/PortfolioManager.h>
#include <TFTrading/Position.h>
#include <TFTrading/Instrument.h>

#include <TFTimeSeries/TimeSeries.h>

#include <TFIndicators/ZigZag.h>

class StrategyEquity {
public:

  typedef ou::tf::CSimulationProvider::pProvider_t pProviderSim_t;

  StrategyEquity( pProviderSim_t pProvider );
  ~StrategyEquity(void);

  void Start( void );  // for simulation
  void Stop( void );

protected:
private:

  typedef ou::tf::CPosition::pOrder_t pOrder_t;
  typedef ou::tf::CPosition::pPosition_t pPosition_t;
  typedef ou::tf::CInstrument::pInstrument_t pInstrument_t;
  typedef ou::tf::CPortfolioManager::pPortfolio_t pPortfolio_t;
  typedef ou::tf::CPortfolioManager::pPosition_t pPosition_t;

  enum enumTradeStates { EPreOpen, EBellHeard, EPauseForQuotes, EAfterBell, ETrading, ECancelling, EGoingNeutral, EClosing, EAfterHours };

  ou::tf::CQuotes m_quotes;
  ou::tf::CTrades m_trades;

  time_duration m_timeOpeningBell, m_timeCancel, m_timeClose, m_timeClosingBell;

  pInstrument_t m_pUnderlying;
  std::string m_sUnderlying;

  pPortfolio_t m_pPortfolio;

  pProviderSim_t m_pProvider;

  pPosition_t m_pPositionLong;
  pPosition_t m_pPositionShort;

  pOrder_t m_pOrder;  // active order

  ou::tf::ZigZag m_zigzagPrice;

  void HandleQuote( const ou::tf::CQuote& );
  void HandleTrade( const ou::tf::CTrade& );

};
