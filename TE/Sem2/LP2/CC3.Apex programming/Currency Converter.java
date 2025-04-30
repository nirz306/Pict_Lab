name->developer console->create two files there, apex classes and pages ->preview 
the controller="" this should have the name of the class written in apex class code 

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
<apex:page controller="CurrencyConverter" applyBodyTag="false" showHeader="true" sidebar="false">
    <apex:form >
        <div style="max-width: 600px; margin: 40px auto; padding: 30px; border: 1px solid #ccc; 
                    border-radius: 10px; box-shadow: 0 4px 10px rgba(0,0,0,0.1); 
                    font-family: Arial, sans-serif; background: #f9f9f9;">
                    
            <h1 style="text-align: center; color: #0070d2;">Dollar to Rupee Converter</h1>

            <!-- Input for USD Amount -->
            <div style="margin-bottom: 15px;">
                <label style="display: block; font-weight: bold;">Enter Amount in USD</label>
                <apex:inputText value="{!amountUSD}" style="width: 100%; padding: 10px; 
                               border: 1px solid #ccc; border-radius: 5px;" required="true"/>
            </div>

            <!-- Convert Button -->
            <div style="text-align: center; margin-top: 20px;">
                <apex:commandButton value="Convert to INR" action="{!convertCurrency}" 
                                   rerender="resultPanel, errorPanel" style="background-color: #28a745; 
                                   color: #fff; padding: 10px 25px; border: none; 
                                   border-radius: 5px; cursor: pointer;"/>
            </div>

            <!-- Error Message -->
            <apex:outputPanel id="errorPanel" rendered="{!NOT(ISBLANK(errorMessage))}" style="text-align: center; margin-top: 20px; color: red;">
                <h3>{!errorMessage}</h3>
            </apex:outputPanel>

            <!-- Result Panel -->
            <apex:outputPanel id="resultPanel" style="text-align: center; margin-top: 20px;">
                <h2 style="color: #333;">Converted Amount: <span style="color: #0070d2;">{!convertedAmount} INR</span></h2>
            </apex:outputPanel>

        </div>
    </apex:form>
</apex:page>
                   

public class CurrencyConverter {

    public String amountUSD { get; set; }
    public Decimal exchangeRate { get; set; }
    public Decimal convertedAmount { get; set; }
    public String errorMessage { get; set; }

    // Constructor to initialize variables
    public CurrencyConverter() {
        amountUSD = '';
        exchangeRate = 83.5;  // Static value for USD to INR exchange rate (This could be dynamic if you fetch from an API)
        convertedAmount = 0;
        errorMessage = '';
    }

    // Method to perform the currency conversion
    public void convertCurrency() {
        // Reset the error message
        errorMessage = '';
        
        // Validate if the amount is numeric and non-negative
        if (!isNumeric(amountUSD)) {
            errorMessage = 'Please enter a valid numeric value.';
            return;
        }
        
        Decimal usdAmount = Decimal.valueOf(amountUSD);
        
        // Ensure the amount is non-negative
        if (usdAmount < 0) {
            errorMessage = 'Please enter a non-negative amount.';
            return;
        }
        
        // Perform the conversion
        convertedAmount = usdAmount * exchangeRate;
    }

    // Helper method to check if the string input is numeric
    public Boolean isNumeric(String value) {
        try {
            // Try parsing the string as a Decimal to check if it's numeric
            Decimal d = Decimal.valueOf(value);
            return true;
        } catch (Exception e) {
            return false;
        }
    }

    // Fetch the live exchange rate (Optional, you could use a public API here)
    public void fetchExchangeRate() {
        // Example: Fetch the exchange rate from an external API (this can be a static value for simplicity)
        // In real applications, you'd use a web service call to fetch live exchange rates.
        // For now, we are using a static value (83.5 for USD to INR).
        exchangeRate = 83.5;
    }
}
