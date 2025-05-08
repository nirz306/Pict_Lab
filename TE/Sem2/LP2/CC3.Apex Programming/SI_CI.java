public class SimpleIntrestCalculator {
    public String principle{get;set;}
    public String years{get;set;}
    public String intrest{get;set;}
    public decimal simpleinterest{get;set;}
    public decimal compoundinterest{get;set;}
    public String errorMessage { get; set; }
    
    public SimpleIntrestCalculator(){
        principle='';
        years='';
        intrest='';
        errorMessage='';
    }
    
    public void calculateSI(){
        errorMessage='';
        if (!isNumeric(principle)) {
            errorMessage = 'Please enter a valid Principle Amount';
            return;
        }
        if ( !isNumeric(years)) {
            errorMessage = 'Please enter valid no of years.';
            return;
        }
        if ( !isNumeric(intrest)) {
            errorMessage = 'Please enter a valid rate of interest';
            return;
        }
        
        Decimal P= Decimal.valueOf(principle);
        Decimal N= Decimal.valueOf(years);
        Decimal R= Decimal.valueOf(intrest);
        
         if (P < 0) {
            errorMessage = 'Please enter a non-negative principle amount.';
            return;
        }
        
        if (N<0) {
            errorMessage = 'Please enter a non-negative years.';
            return;
        }
        
         if (R<0) {
            errorMessage = 'Please enter a non-negative rate of inetrest.';
            return;
        }

        simpleinterest = ((p*n*r)/100)+p;    
       
    }
    
     public Boolean isNumeric(String value) {
        try {
             Decimal d = Decimal.valueOf(value);
            return true;
        } catch (Exception e) {
            return false;
        }
    }
    
     
    
}
//-----------------------------------------------------------------------------------------------------

<apex:page controller="SimpleIntrestCalculator">
 
    <apex:form > 
		
             
           
    	<label >Enter Principle Amount</label>
    	<apex:inputText value="{!principle}"/>
    
     <label >Enter Duration(yrs)</label>	
    <apex:inputText value="{!years}"/>
    
     <label >Enter Rate of Interest(%)</label>
    <apex:inputText value="{!intrest}"/>
    
   <apex:commandButton value="Find SI" action="{!calculateSI}" rerender="resultPanel, errorPanel" />
           
     <apex:outputPanel id="errorPanel" rendered="{!NOT(ISBLANK(errorMessage))}" >
                <h3>{!errorMessage}</h3>
            </apex:outputPanel>
    
            <apex:outputPanel id="resultPanel"  >
                <h2  > Simple Interest: <span  >{!simpleinterest } </span></h2>
            </apex:outputPanel>
                
           </apex:form>
</apex:page>
