// Class
public class MatrixMultiplicationController {
    public String input1 { get; set; }
    public String input2 { get; set; }
    public String result { get; set; }

    public void multiplyMatrices() {
        try {
            List<List<Integer>> m1 = parseMatrix(input1);
            List<List<Integer>> m2 = parseMatrix(input2);
            List<List<Integer>> product = multiply(m1, m2);
            result = JSON.serialize(product);
        } catch (Exception e) {
            result = 'Error: ' + e.getMessage(); // gracefully show the error
        }
    }

    private List<List<Integer>> parseMatrix(String input) {
        List<List<Integer>> matrix = new List<List<Integer>>();
        for (String row : input.split('\n')) {
            List<Integer> r = new List<Integer>();
            for (String num : row.split(',')) {
                r.add(Integer.valueOf(num.trim()));
            }
            matrix.add(r);
        }
        return matrix;
    }

    private List<List<Integer>> multiply(List<List<Integer>> A, List<List<Integer>> B) {
        Integer rowsA = A.size();
        Integer colsA = A[0].size();
        Integer rowsB = B.size();
        Integer colsB = B[0].size();

        if (colsA != rowsB) {
            throw new IllegalArgumentException('Number of columns in Matrix A must match rows in Matrix B.');
        }

        List<List<Integer>> result = new List<List<Integer>>();

        for (Integer i = 0; i < rowsA; i++) {
            List<Integer> row = new List<Integer>();
            for (Integer j = 0; j < colsB; j++) {
                Integer sum = 0;
                for (Integer k = 0; k < colsA; k++) {
                    sum += A[i][k] * B[k][j];
                }
                row.add(sum);
            }
            result.add(row);
        }
        return result;
    }
}

//visualforce pages
<apex:page controller="MatrixMultiplicationController">
    <apex:form>
        <apex:pageBlock title="Matrix Multiplication">
            <apex:pageBlockSection columns="1">
                <apex:inputTextarea value="{!input1}" rows="4" cols="40" label="Matrix A (comma-separated rows, newline-separated)"/>
                <apex:inputTextarea value="{!input2}" rows="4" cols="40" label="Matrix B (comma-separated rows, newline-separated)"/>
                <apex:commandButton value="Multiply" action="{!multiplyMatrices}" rerender="resultPanel"/>
            </apex:pageBlockSection>
            <apex:outputPanel id="resultPanel">
                <apex:outputText label="Result:" value="{!result}" escape="false"/>
            </apex:outputPanel>
        </apex:pageBlock>
    </apex:form>
</apex:page>
