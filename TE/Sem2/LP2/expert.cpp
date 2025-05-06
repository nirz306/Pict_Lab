#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>

using namespace std;

struct StockAnalysis {
    float pe_ratio; //It tells you how much investors are willing to pay for each dollar of a company’s earnings.
    float debt_to_equity;
    float ebitda_growth;
    float roce;
    float current_price;
    float week_high;
    float week_low;
    int sector;
    float risk_tolerance;
    int investment_horizon;
    float market_cap;
};

const vector<string> sectors = {
    "Automobile", "Banking/Financial", "Pharmaceutical", 
    "Information Technology", "FMCG", "Infrastructure", 
    "Manufacturing", "Energy"
};

float get_numeric_input(const string& prompt) {
    float value;
    cout << prompt;
    while (!(cin >> value)) {
        cout << "Please enter a valid number: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    return value;
}

int get_category_input(const string& prompt, const vector<string>& options) {
    cout << prompt << endl;
    for (size_t i = 0; i < options.size(); ++i) {
        cout << i+1 << ". " << options[i] << endl;
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

StockAnalysis get_user_input() {
    StockAnalysis analysis;

    cout << "=== Company Fundamentals Analysis ===" << endl;
    analysis.pe_ratio = get_numeric_input("Enter current P/E ratio: ");
    analysis.debt_to_equity = get_numeric_input("Enter Debt-to-Equity ratio: ");
    analysis.ebitda_growth = get_numeric_input("Enter EBITDA growth (YoY %) : ");
    analysis.roce = get_numeric_input("Enter Return on Capital Employed (ROCE %): ");
    analysis.market_cap = get_numeric_input("Enter market capitalization (in crore INR): ");

    cout << "\n=== Technical Analysis ===" << endl;
    analysis.current_price = get_numeric_input("Enter current stock price: ");
    analysis.week_high = get_numeric_input("Enter 52-week high price: ");
    analysis.week_low = get_numeric_input("Enter 52-week low price: ");

    cout << "\n=== Sector Analysis ===" << endl;
    analysis.sector = get_category_input("Select industry sector:", sectors);

    cout << "\n=== Investor Profile ===" << endl;
    analysis.risk_tolerance = get_numeric_input("What percentage loss can you tolerate in a month? (0-100): ");
    analysis.investment_horizon = get_numeric_input("Planned investment duration (in months): ");

    return analysis;
}

void analyze_stock(const StockAnalysis& sa) {
    float fundamental_score = 0;
    float technical_score = 0;
    float sector_score = 0;
    
    // Fundamental analysis scoring
    fundamental_score += (sa.pe_ratio < 25) ? 2 : (sa.pe_ratio < 35) ? 1 : -1;
    fundamental_score += (sa.debt_to_equity < 1) ? 2 : (sa.debt_to_equity < 2) ? 1 : -2;
    fundamental_score += (sa.ebitda_growth > 15) ? 2 : (sa.ebitda_growth > 8) ? 1 : -1;
    fundamental_score += (sa.roce > 20) ? 2 : (sa.roce > 12) ? 1 : -1;

    // Technical analysis
    float price_position = (sa.current_price - sa.week_low) / (sa.week_high - sa.week_low);
    technical_score += (price_position < 0.3) ? 2 : (price_position < 0.7) ? 1 : -1;
    technical_score += (sa.current_price > sa.week_high * 0.9) ? -1 : 0;

    // Sector analysis
    const vector<int> favorable_sectors = {0, 1, 2};
    bool is_favorable_sector = find(favorable_sectors.begin(), favorable_sectors.end(), sa.sector) != favorable_sectors.end();
    sector_score = is_favorable_sector ? 2 : 0;

    // Risk assessment
    float risk_factor = (100 - sa.risk_tolerance)/20.0;
    float reward_factor = (fundamental_score + technical_score + sector_score) * 
                         log(sa.market_cap/1000) * 
                         (sa.investment_horizon/12.0);

    cout << "\n=== Analysis Results ===" << endl;
    cout << "Risk Level: " << min(100.0f, max(0.0f, risk_factor * 15)) << "%\n";
    cout << "Potential Reward: " << min(200.0f, max(0.0f, reward_factor * 10)) << "%\n\n";

    cout << "Detailed Assessment:\n";
    // Fundamental analysis comments
    if (fundamental_score < 2) {
        cout << "- Weak fundamentals: High valuation or poor financial health\n";
    }
    else if (fundamental_score >= 2 && fundamental_score < 4) {
        cout << "- Moderate fundamentals: Average financial metrics\n";
    }
    else if (fundamental_score >= 4 && fundamental_score < 6) {
        cout << "- Strong fundamentals: Good financial health\n";
    }
    else {
        cout << "- Excellent fundamentals: Very attractive valuation\n";
    }

    // Technical analysis comments
    if (technical_score > 3) {
        cout << "- Strong technical position: Good entry point\n";
    }
    else if (technical_score >= 1 && technical_score <= 3) {
        cout << "- Neutral technical position: Wait for better entry\n";
    }
    else {
        cout << "- Weak technical position: Overbought territory\n";
    }

    if (price_position > 0.7) {
        cout << "- Stock trading near 52-week high\n";
    }
    else if (price_position < 0.3) {
        cout << "- Stock trading near 52-week low\n";
    }

    // Sector analysis comments
    if (is_favorable_sector) {
        cout << "- Sector outlook: Positive growth potential\n";
    }
    else {
        cout << "- Sector outlook: Normal market conditions\n";
    }

    // Investment horizon comments
    if (sa.investment_horizon < 6) {
        cout << "- Investment horizon is too short for this stock. pls consider a longer term investment or choose other options. \n";
    }
    else if (sa.investment_horizon >= 6 && sa.investment_horizon < 12) {
        cout << "- Investment horizon: Moderate term holding suggested\n";
    }
    else {
        cout << "- Investment horizon: Suitable for long-term investment\n";
    }

    // Final recommendation
    cout << "\nFinal Recommendation:\n";
    if (reward_factor > 7 && risk_factor < 4) {
        cout << "Strong conviction to buy it. Immediate investment recommended. \n";
    } 
    else if (reward_factor > 4) {
        if (price_position < 0.4) {
            cout << "Moderate Buy: Accumulate on dips below " << sa.week_low * 1.05 << endl;
        }
        else {
            cout << "Moderate Buy: Consider staggered investment\n";
        }
    }
    else if (reward_factor > 2) {
        cout << "Hold: Maintain existing position\n";
    }
    else {
        if (sa.risk_tolerance > 30) {
            cout << "Speculative opportunity. it is High risk, only for risk-tolerant investors\n";
        }
        else {
            cout << "Avoid this one. Better opportunities might be available elsewhere. \n";
        }
    }
}


int main() {
    cout << "Stock Market Expert System  \n";
    cout << "-----------------------------------------\n";
    StockAnalysis analysis = get_user_input();
    analyze_stock(analysis);
    return 0;
}
