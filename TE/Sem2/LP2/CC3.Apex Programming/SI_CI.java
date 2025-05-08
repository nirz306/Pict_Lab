public class SimpleCompoundCalculator {
    public Double principle { get; set; }
    public Double years { get; set; }
    public Double intrest { get; set; }
    public String errorMessage { get; set; }

    public Double simpleinterest { get; set; }
    public Double compoundinterest { get; set; }

    public void calculateSI() {
        if (principle == null || years == null || intrest == null) {
            errorMessage = 'Please fill in all the fields.';
            simpleinterest = null;
            compoundinterest = null;
            return;
        }
        
        errorMessage = '';
        simpleinterest = (principle * years * intrest) / 100;
        compoundinterest = principle * Math.pow(1 + intrest / 100, years) - principle;
    }
}

//-----------------------------------------------------------------------------------------------------

<apex:page controller="SimpleCompoundCalculator">
    <apex:form >
        <apex:pageBlock title="Interest Calculator" mode="edit">
            <apex:pageBlockSection columns="1">
                <apex:outputLabel value="Enter Principle Amount" for="p"/>
                <apex:inputText id="p" value="{!principle}" />

                <apex:outputLabel value="Enter Duration (yrs)" for="y"/>
                <apex:inputText id="y" value="{!years}" />

                <apex:outputLabel value="Enter Rate of Interest (%)" for="r"/>
                <apex:inputText id="r" value="{!intrest}" />

                <apex:commandButton value="Find Interest" action="{!calculateSI}" rerender="resultPanel, errorPanel"/>
            </apex:pageBlockSection>

            <apex:outputPanel id="errorPanel" rendered="{!NOT(ISBLANK(errorMessage))}">
                <h3 style="color:red;">{!errorMessage}</h3>
            </apex:outputPanel>

            <apex:outputPanel id="resultPanel">
                <h2>Simple Interest: <span>{!simpleinterest}</span></h2>
                <h2>Compound Interest: <span>{!compoundinterest}</span></h2>
            </apex:outputPanel>
        </apex:pageBlock>
    </apex:form>
</apex:page>
