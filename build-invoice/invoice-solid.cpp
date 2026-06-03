// 01-invoice-srp-ocp.cpp
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <stdexcept>
#include <memory>

using namespace std;

struct LineItem {
    string sku;
    int quantity{0};
    double unitPrice{0.0};
};
struct Invoice {
    double subtotal;
    double discount_total;
    double tax;
    double grand_total;
};
class DiscountService{   
    public:
        virtual ~DiscountService() = default;
        virtual double getDiscountTotal(const double subtotal) = 0;
};
class DiscountPercentOff: public DiscountService{
    private:
        double percent;
    public:
        DiscountPercentOff(double percent){
            this->percent = percent;
        }
        double getDiscountTotal(const double subtotal) override {
            return subtotal * (percent/ 100.0);
        }
};
class DiscountFlatOff: public DiscountService{
    private:
        double amount;
    public:
        DiscountFlatOff(double amount){
            this->amount = amount;
        }
        double getDiscountTotal(const double subtotal) override {
            return amount;
        }
};
class NotificationService{
    public:
        virtual ~NotificationService() = default;
        virtual void send(const string& email, const string& message) = 0;
};
class EmailNotificationService: public NotificationService{
    public:
        void send(const string& email, const string& message) override {
            cout << "[SMTP] Sending invoice to " << email << "...\n";
        }
};
class TaxService{
    public:
        virtual ~TaxService() = default;
        virtual double getTax(const double subtotal, const double discount_total) = 0;
};
class TaxPercentOff: public TaxService{
    private:
        double percent;
    public:
        TaxPercentOff(double percent){
            this->percent = percent;
        }
        double getTax(const double subtotal, const double discount_total) override {
            return (subtotal - discount_total) * (percent / 100.0);
        }
};
class LoggerService{
    public:
        virtual ~LoggerService() = default;
        virtual void log(const string& email, const double grand_total) = 0;
};
class ConsoleLoggerService: public LoggerService{
    public:
        void log(const string& email, const double grand_total) override {
            cout << "[LOG] Invoice processed for " << email << " total=" << grand_total << "\n";
        }
};
class InvoiceGenerationService{
    private:
        Invoice bill;
        TaxService& taxService;
    public:
        InvoiceGenerationService(const vector<LineItem>& items, const vector<unique_ptr<DiscountService>>& discounts, TaxService& taxService) : taxService(taxService) {
            // pricing
            bill.subtotal = getSubtotal(items);

            // discounts
            bill.discount_total = getDiscountTotal(discounts);

            // tax inline
            bill.tax = taxService.getTax(bill.subtotal, bill.discount_total);
            bill.grand_total = getGrandTotal();
        }
        double getSubtotal(const vector<LineItem>& items) {
            double subtotal = 0.0;
            for (auto& it : items) subtotal += it.unitPrice * it.quantity;
            return subtotal;
        }
        double getDiscountTotal(const vector<unique_ptr<DiscountService>>& discounts) {
            double discount_total = 0.0;
            for (auto& discount : discounts) {
                discount_total += discount->getDiscountTotal(bill.subtotal);
            }
            return discount_total;
        }
        double getGrandTotal() {
            double grand_total = bill.subtotal - bill.discount_total + bill.tax;
            return grand_total;
        }
        Invoice getInvoice() {
            return bill;
        }
}; 

class InvoiceReceiptService {
private:
    Invoice bill;
    LoggerService& loggerService;
    TaxService& taxService;
    NotificationService& notificationService;
public:
    InvoiceReceiptService(LoggerService& loggerService, TaxService& taxService, NotificationService& notificationService) : loggerService(loggerService), taxService(taxService), notificationService(notificationService) {}
    string process(const string& email, const vector<LineItem>& items, const vector<unique_ptr<DiscountService>>& discounts) {
        InvoiceGenerationService invoiceGenerationService(items, discounts, taxService);
        bill = invoiceGenerationService.getInvoice();
        // Invoice Rendering
        string rendered = render(items, bill);

        // email I/O inline (tight coupling)
        notificationService.send(email, rendered);

        // logging inline
        loggerService.log(email, computeTotal());

        return rendered;
    }
    string render(const vector<LineItem>& items, const Invoice& bill) {
            // rendering inline (pretend PDF)
            ostringstream pdf;
            pdf << "INVOICE\n";
            for (auto& it : items) {
                pdf << it.sku << " x" << it.quantity << " @ " << it.unitPrice << "\n";
            }
            pdf << "Subtotal: " << bill.subtotal << "\n"
                << "Discounts: " << bill.discount_total << "\n"
                << "Tax: " << bill.tax << "\n"
                << "Total: " << bill.grand_total << "\n";
            return pdf.str();
        }
    // helper used by ad-hoc tests; also messy on purpose
    double computeTotal() {
        return bill.grand_total;
    }
};

int main() {
    
    // Create items
    vector<LineItem> items = { {"ITEM-001", 3, 100.0}, {"ITEM-002", 1, 250.0} };    
    vector<unique_ptr<DiscountService>> discounts;
    discounts.push_back(make_unique<DiscountPercentOff>(10.0));
    discounts.push_back(make_unique<DiscountFlatOff>(50.0));
    TaxPercentOff tax(18);
    EmailNotificationService emailService;
    ConsoleLoggerService logger;    
    InvoiceReceiptService svc(logger, tax, emailService); 
    cout << svc.process("customer@example.com", items, discounts) << endl;
    return 0;
}