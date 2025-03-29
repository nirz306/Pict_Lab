#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <limits>

using namespace std;

struct InvestmentProfile {
    float investment_amount;
    int investment_horizon;     // in months
    int risk_tolerance;         // 0: low, 1: moderate, 2: high
    int financial_goal;         // 0: Retirement, 1: Wealth Creation, etc.
    float expected_return;      // in percentage
    int investment_frequency;   // 0: One-time, 1: Monthly SIP, 2: Quarterly
};

const vector<string> risk_levels = {"Low", "Moderate", "High"};
const vector<string> amount_ranges = {
    "Below 1 Lakh", "1-10 Lakhs", "10-50 Lakhs", "Above 50 Lakhs"
};
const vector<string> financial_goals = {
    "Retirement Planning", "Wealth Creation", "Child's Education", "Buying a House", "Emergency Fund"
};
const vector<string> investment_frequencies = {
    "One-time Investment", "Monthly SIP", "Quarterly Investment"
};

float get_numeric_input(const string& prompt) {
    float value;
    cout << prompt;
    while (!(cin >> value) || value < 0) {
        cout << "Please enter a valid positive number: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    return value;
}

int get_category_input(const string& prompt, const vector<string>& options) {
    cout << prompt << endl;
    for (size_t i = 0; i < options.size(); ++i) {
        cout << i + 1 << ". " << options[i] << endl;
    }

    int choice;
    while (true) {
        cout << "Enter choice (1-" << options.size() << "): ";
        cin >> choice;
        if (choice >= 1 && choice <= static_cast<int>(options.size())) {
            return choice - 1;
        }
        cout << "Invalid choice. Please try again.\n";
    }
}

InvestmentProfile get_user_input() {
    InvestmentProfile profile;

    cout << "=== Investment Profile Assessment ===\n";
    
    profile.investment_amount = get_numeric_input("How much money do you plan to invest (in INR lakhs)? ");
    
    // Categorize investment amount
    int amount_category;
    if (profile.investment_amount < 1) amount_category = 0;
    else if (profile.investment_amount <= 10) amount_category = 1;
    else if (profile.investment_amount <= 50) amount_category = 2;
    else amount_category = 3;

    cout << "Your investment falls in category: " << amount_ranges[amount_category] << "\n\n";

    profile.investment_horizon = get_numeric_input("Enter investment duration (in months): ");
    
    profile.risk_tolerance = get_category_input("Select your risk tolerance level:", risk_levels);

    profile.financial_goal = get_category_input("Select your financial goal:", financial_goals);

    profile.expected_return = get_numeric_input("What is your expected annual return (%)? ");

    profile.investment_frequency = get_category_input("Choose your investment frequency:", investment_frequencies);

    return profile;
}

void provide_recommendations(const InvestmentProfile& ip) {
    cout << "\n=== Investment Recommendations ===\n";
    cout << "Based on your profile:\n";
    cout << "- Investment Amount: " << ip.investment_amount << " Lakhs\n";
    cout << "- Time Horizon: " << ip.investment_horizon << " months\n";
    cout << "- Risk Tolerance: " << risk_levels[ip.risk_tolerance] << "\n";
    cout << "- Financial Goal: " << financial_goals[ip.financial_goal] << "\n";
    cout << "- Expected Return: " << ip.expected_return << "%\n";
    cout << "- Investment Frequency: " << investment_frequencies[ip.investment_frequency] << "\n\n";

    // Recommendations based on risk and goal
    if (ip.risk_tolerance == 0) {  // Low risk
        cout << "Recommended Investment Strategy: Conservative\n";
        cout << "Focus: Stable, blue-chip stocks and low-risk assets\n";

        if (ip.financial_goal == 0) {  // Retirement Planning
            cout << "\nSuggested Options:\n";
            cout << "1. Fixed Deposits (FDs) - 6-7% returns\n";
            cout << "2. Government Bonds - Risk-free returns\n";
        } else if (ip.financial_goal == 1) {  // Wealth Creation
            cout << "\nSuggested Stocks:\n";
            cout << "1. HDFC Bank - Banking sector, stable growth\n";
            cout << "2. TCS - IT sector, consistent dividends\n";
        }

        cout << "\nExpected Annual Return: 6-12%\n";
        cout << "Volatility: Low (Beta ~0.7)\n";

    } else if (ip.risk_tolerance == 1) {  // Moderate risk
        cout << "Recommended Investment Strategy: Balanced\n";
        cout << "Focus: Mix of growth and stable stocks\n";

        if (ip.financial_goal == 2) {  // Child's Education
            cout << "\nSuggested Options:\n";
            cout << "1. Large-cap Mutual Funds - HDFC Top 100 Fund\n";
            cout << "2. Balanced Advantage Funds - ICICI Pru Balanced Advantage\n";
        } else {  // Wealth Creation or House
            cout << "\nSuggested Stocks:\n";
            cout << "1. Reliance Industries - Diversified, moderate growth\n";
            cout << "2. Bajaj Finance - Financial services, good returns\n";
        }

        cout << "\nExpected Annual Return: 10-18%\n";
        cout << "Volatility: Moderate (Beta ~1.0)\n";

    } else {  // High risk
        cout << "Recommended Investment Strategy: Aggressive\n";
        cout << "Focus: High-growth, volatile stocks\n";

        if (ip.financial_goal == 3) {  // Buying a House
            cout << "\nSuggested Stocks:\n";
            cout << "1. Adani Enterprises - Infrastructure, high volatility\n";
            cout << "2. Tata Motors - Auto sector, high growth potential\n";
        } else {  // Wealth Creation or Emergency Fund
            cout << "\nSuggested Stocks:\n";
            cout << "1. Zomato - New-age tech, speculative growth\n";
            cout << "2. Suzlon Energy - Renewable energy, speculative\n";
        }

        cout << "\nExpected Annual Return: 20-30%\n";
        cout << "Volatility: High (Beta ~1.5)\n";
    }

    // Portfolio Allocation based on frequency
    cout << "\nSuggested Portfolio Allocation:\n";
    if (ip.investment_frequency == 0) {  // One-time Investment
        cout << "- 70% in primary stock/fund\n";
        cout << "- 30% in secondary option\n";
    } else if (ip.investment_frequency == 1) {  // Monthly SIP
        cout << "- 60% in SIP funds\n";
        cout << "- 40% in large-cap stable stocks\n";
    } else {  // Quarterly Investment
        cout << "- 50% in equity stocks\n";
        cout << "- 30% in debt mutual funds\n";
        cout << "- 20% in cash/reserve\n";
    }

    cout << "\nNote: These recommendations are based on general market trends as of March 2025. Consult a financial advisor for personalized guidance.\n";
}

int main() {
    cout << "Personal Investment Advisor System\n";
    cout << "---------------------------------\n";
    
    InvestmentProfile profile = get_user_input();
    provide_recommendations(profile);
    
    return 0;
}
