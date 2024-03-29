#ifndef _HISTORY_TRANSACTION_CPP_
#define _HISTORY_TRANSACTION_CPP_

#include <cassert>
#include <iomanip>
#include <iostream>

#include "project4.hpp"
#include "History.hpp"
#include "Transaction.hpp"

////////////////////////////////////////////////////////////////////////////////
// Definitions for Transaction class
////////////////////////////////////////////////////////////////////////////////
//
//

// Constructor
// TASK 1
//

Transaction::Transaction( std::string ticker_symbol, unsigned int day_date, unsigned int month_date,
		unsigned year_date, bool buy_sell_trans, unsigned int number_shares, double trans_amount)
{
	symbol = ticker_symbol;
	day = day_date;
	month = month_date;
	year = year_date;

	if (buy_sell_trans)
	{
		trans_type = "Buy";
	}
	else
	{
		trans_type = "Sell";
	}

	shares = number_shares;
	amount = trans_amount;

	trans_id = assigned_trans_id;
	assigned_trans_id++;

	acb = 0.00;
	acb_per_share = 0.00;
	share_balance = 0.00;
	cgl = 0.00;

	p_next = nullptr;
}

// Destructor
// TASK 1
//

Transaction::~Transaction()
{
	p_next = nullptr;
	delete p_next;
}

// Overloaded < operator.
// TASK 2
//

bool Transaction::operator <( Transaction const &other )
{
	if (	(year < other.year)
			||( (year <= other.year) && (month < other.month) )
			||( (year <= other.year) && (month <= other.month) && (day < other.day) ) )
	{
		return true;
	}
	else
	{
		return false;
	}
}

// GIVEN
// Member functions to get values.
//

std::string Transaction::get_symbol() const { return symbol; }
unsigned int Transaction::get_day() const { return day; }
unsigned int Transaction::get_month() const { return month; }
unsigned int Transaction::get_year() const { return year; }
unsigned int Transaction::get_shares() const { return shares; }
double Transaction::get_amount() const { return amount; }
double Transaction::get_acb() const { return acb; }
double Transaction::get_acb_per_share() const { return acb_per_share; }
unsigned int Transaction::get_share_balance() const { return share_balance; }
double Transaction::get_cgl() const { return cgl; }
bool Transaction::get_trans_type() const { return (trans_type == "Buy") ? true: false ; }
unsigned int Transaction::get_trans_id() const { return trans_id; }
Transaction *Transaction::get_next() { return p_next; }

// GIVEN
// Member functions to set values.
//

void Transaction::set_acb( double acb_value ) { acb = acb_value; }
void Transaction::set_acb_per_share( double acb_share_value ) { acb_per_share = acb_share_value; }
void Transaction::set_share_balance( unsigned int bal ) { share_balance = bal ; }
void Transaction::set_cgl( double value ) { cgl = value; }
void Transaction::set_next( Transaction *p_new_next ) { p_next = p_new_next; }

// GIVEN
// Print the transaction.
//

void Transaction::print() {
  std::cout << std::fixed << std::setprecision(2);
  std::cout << std::setw(4) << get_trans_id() << " "
    << std::setw(4) << get_symbol() << " "
    << std::setw(4) << get_day() << " "
    << std::setw(4) << get_month() << " "
    << std::setw(4) << get_year() << " ";


  if ( get_trans_type() ) {
    std::cout << "  Buy  ";
  } else { std::cout << "  Sell "; }

  std::cout << std::setw(4) << get_shares() << " "
    << std::setw(10) << get_amount() << " "
    << std::setw(10) << get_acb() << " " << std::setw(4) << get_share_balance() << " "
    << std::setw(10) << std::setprecision(3) << get_acb_per_share() << " "
    << std::setw(10) << std::setprecision(3) << get_cgl()
    << std::endl;
}

////////////////////////////////////////////////////////////////////////////////
// Definitions for the History class
////////////////////////////////////////////////////////////////////////////////
//
//

// Constructor
// TASK 3
//

History::History()
{
	p_head = nullptr;
}

// Destructor
// TASK 3
//



History::~History()
{
	while (p_head != nullptr)
	{
		Transaction *p_runner {p_head};
		p_head = p_head->get_next();

		delete p_runner;
	}
}


// read_transaction(...): Read the transaction history from file.
// TASK 4
//

void History::read_history()
{
	ece150::open_file();
	while (ece150::next_trans_entry())
	{
		Transaction* input_trans
		{ new Transaction
			{
		ece150::get_trans_symbol(),
		ece150::get_trans_day(),
		ece150::get_trans_month(),
		ece150::get_trans_year(),
		ece150::get_trans_type(),
		ece150::get_trans_shares(),
		ece150::get_trans_amount()
			}
		};

		insert (input_trans);
	}
	ece150::close_file();
}

// insert(...): Insert transaction into linked list.
// TASK 5
//

void History::insert(Transaction *p_new_trans)
{
	if (p_head == nullptr)
	{
		p_head = p_new_trans;
	}
	else
	{
		Transaction *p_transverse {p_head};
		while (p_transverse->get_next() != nullptr)
		{
			p_transverse = p_transverse->get_next();
		}
		p_transverse->set_next(p_new_trans);
	}
}

// sort_by_date(): Sort the linked list by trade date.
// TASK 6
//

void History::sort_by_date()
{
	if (p_head != nullptr || p_head->get_next() != nullptr)
	{
		Transaction * p_temp1 {p_head};
		Transaction * p_sorted {nullptr};

		p_head = p_head->get_next();
		p_temp1->set_next(nullptr);
		p_sorted = p_temp1;

		while (p_head != nullptr)
		{
			p_temp1 = p_head;
			p_head = p_head->get_next();
			p_temp1->set_next(nullptr);

			if ( (*p_temp1 < *p_sorted) ||
					( (p_temp1->get_year() == p_sorted->get_year())
					&& (p_temp1->get_month() == p_sorted->get_month())
					&& (p_temp1->get_day() == p_sorted->get_day())
					&& (p_temp1->get_trans_id() < p_sorted->get_trans_id()) ) )
			{
				p_temp1->set_next(p_sorted);
				p_sorted = p_temp1;
			}
			else
			{
				Transaction * p_temp2 {p_sorted};
				while (p_temp2->get_next() != nullptr)
				{
					if ( *p_temp1 < *p_temp2->get_next()) {break;}
					p_temp2 = p_temp2->get_next();
				}
				p_temp1->set_next(p_temp2->get_next());
				p_temp2->set_next(p_temp1);
			}
		}
		p_head = p_sorted;
	}
}


// update_acb_cgl(): Updates the ACB and CGL values.
// TASK 7
//

void History::update_acb_cgl()
{
	Transaction * p_holder {p_head};
	long double share_balance {0.00};
	long double acb {0.00};
	long double acb_per_share {0.00};

	while (p_head != nullptr )
	{
		if (p_head->get_trans_type() == true)
		{
			p_head->set_acb( acb + p_head->get_amount() );
			acb = p_head->get_acb();

			p_head->set_share_balance(share_balance + p_head->get_shares() );
			share_balance = p_head->get_share_balance();

			p_head->set_acb_per_share( acb / share_balance );
			acb_per_share = p_head->get_acb_per_share();

			p_head->set_cgl( 0.00 );

		}
		else
		{
			p_head->set_acb( acb - (p_head->get_shares() * acb_per_share) );
			acb = p_head->get_acb();

			p_head->set_share_balance( share_balance - p_head->get_shares() );
			share_balance = p_head->get_share_balance();

			p_head->set_acb_per_share( acb_per_share );
			acb_per_share = p_head->get_acb_per_share();

			p_head->set_cgl( p_head->get_amount() - (p_head->get_shares() * acb_per_share) );

		}
		p_head = p_head->get_next();
	}
	p_head = p_holder;
}

// compute_cgl(): )Compute the CGL.
// TASK 8

double History::compute_cgl (unsigned int year)
{
	Transaction *p_runner {p_head};
	long double cgl_year {0.0};
	while (p_runner != nullptr)
	{
		if (p_runner->get_year() == year)
		{
			cgl_year += p_runner->get_cgl();
		}
		p_runner = p_runner->get_next();
	}
	return cgl_year;
}

// print() Print the transaction history.
//TASK 9
//

void History::print()
{
	Transaction *p_runner {p_head};

	std::cout << "========== BEGIN TRANSACTION HISTORY ============"<< std::endl;

	while (p_runner != nullptr)
	{
		p_runner->print();
		p_runner = p_runner->get_next();
	}

	std::cout << "========== END TRANSACTION HISTORY ============"<< std::endl;
}

// GIVEN
// get_p_head(): Full access to the linked list.
//

Transaction *History::get_p_head() { return p_head; }

#endif
