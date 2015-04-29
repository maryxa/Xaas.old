#ifndef XACURRENCY_H
#define XACURRENCY_H

#include <XaLibAction.h>

class XaCurrency : public XaLibAction {

    private:

		void Dispatcher(const string &CalledEvent);

		void XaCurrencyRateAddFrm();
		void XaCurrencyRateAdd();
		void XaCurrencyRateList();
		
	protected:

	public:

		XaCurrency();
		~XaCurrency();

		double CalculateCurrencyRate(string FromCurrency,string ToCurrency,string Date);
		double CalculateMonthlyCurrencyRate(string FromCurrency,string ToCurrency,string Year,string Month);
};
#endif
