//apex clases code 
public class linear {
public String inputNumbers { get; set; }
    public Integer target { get; set; }
    public String result { get; set; }

    public void search() {
        List<String> numStrs = inputNumbers != null ? inputNumbers.split(',') : new List<String>();
        for (Integer i = 0; i < numStrs.size(); i++) {
            if (String.isNotBlank(numStrs[i]) && Integer.valueOf(numStrs[i].trim()) == target) {
                result = 'Found at index: ' + i;
                return;
            }
        }
        result = 'Not found';
    }
}

//visual force page code 
<apex:page controller="linear">
    <apex:form>
        <apex:pageBlock title="Linear Search App">
            <apex:pageBlockSection>
                <apex:inputText value="{!inputNumbers}" label="Numbers (comma-separated)" />
                <apex:inputText value="{!target}" label="Target Number" />
                <apex:commandButton value="Search" action="{!search}" />
                <apex:outputText value="{!result}" style="font-weight:bold; display:block; margin-top:10px;" />
            </apex:pageBlockSection>
        </apex:pageBlock>
    </apex:form>
</apex:page>
