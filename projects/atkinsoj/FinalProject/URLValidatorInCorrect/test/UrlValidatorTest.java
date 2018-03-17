

import java.util.Random;

import junit.framework.TestCase;

//You can use this as a skeleton for your 3 different test approach
//It is an optional to use this file, you can generate your own test file(s) to test the target function!
// Again, it is up to you to use this file or not!





public class UrlValidatorTest extends TestCase {


   public UrlValidatorTest(String testName) {
      super(testName);
   }

   
   
   public void testManualTest()
   {
//You can use this function to implement your manual testing	   
	   
   }
   
   
   public void testYourFirstPartition()
   {
	 //You can use this function to implement your First Partition testing	   

   }
   
   public void testYourSecondPartition(){
		 //You can use this function to implement your Second Partition testing	   

   }
   //You need to create more test cases for your Partitions if you need to 
   
   public void testIsValid()
   {
	   //You can use this function for programming based testing

       UrlValidator urlValidator = new UrlValidator(UrlValidator.ALLOW_ALL_SCHEMES);
       setUpRandom();
      
       // Perform a simple test to fail fast. 
       assertTrue("Simple test of example URL", urlValidator.isValid("http://www.google.com"));

       StringBuilder testUrlBuffer;
       StringPair stringPair;
       boolean expectedResult, result;
       String testUrl;
       int successCases = 0, failedCases = 0;
 
       
       for (int i = 0; i < 800000; i++) {

           testUrlBuffer = new StringBuilder();
           expectedResult = true;
           
           stringPair = generateRandomScheme();
           testUrlBuffer.append(stringPair.elem);
           expectedResult &= stringPair.valid;
           
           stringPair = generateRandomHostname();
           testUrlBuffer.append(stringPair.elem);
           expectedResult &= stringPair.valid;

           stringPair = generateRandomPort();
           testUrlBuffer.append(stringPair.elem);
           expectedResult &= stringPair.valid;

           stringPair = generateRandomPath();
           testUrlBuffer.append(stringPair.elem);
           expectedResult &= stringPair.valid;

           stringPair = generateRandomQuery();
           testUrlBuffer.append(stringPair.elem);
           expectedResult &= stringPair.valid;
           
           testUrl = testUrlBuffer.toString();

           result = urlValidator.isValid(testUrl);
           
           if ( assertBooleanPart(expectedResult + ": " + testUrl, expectedResult, result) ) {
               successCases++;
           } else {
               failedCases++;
           }
       }
       
       System.out.println("RESULTS: " + failedCases + " failed of " + 
         (failedCases + successCases) + " total.");
       assertEquals("No failed cases", 0, failedCases);
   }
   
   private boolean assertBooleanPart(String message, boolean expected, boolean actual) {
       if (expected != actual) { 
           System.out.println("FAIL: " + message);
           return false;
       }
       
       return true;
   }

   private Random _random;

   private void setUpRandom() {
       _random = new java.util.Random();
       long seed = _random.nextLong();
       _random.setSeed(seed);
       System.out.println("Seed set to: " + seed);
   }
   
   private StringPair generateRandomScheme() {
       
       return new StringPair("http://", true);
   }

   private StringPair generateRandomHostname() {
       return new StringPair("www.example.com", true);
   }
   
   private StringPair generateRandomPort() {

       String port = "";
       boolean valid = true;
       if (_random.nextInt(1000) == 0 ) {
           port = ":" + Math.pow(2,16) + _random.nextInt(1000);
           valid = false;
       }
       
       if (_random.nextInt(10) > 7) {
           port = ":" + _random.nextInt( (int)Math.pow(2,16) );
           if (port == ":0") {
               valid = false;
           }
       }
       
       return new StringPair(port, valid);
   }
   
   private StringPair generateRandomPath() {
       StringBuffer buf = new StringBuffer();
       if (Math.random() <= .95) { 
           buf.append("/");
       }
       return new StringPair("/blah", true);
   }
   
   private StringPair generateRandomQuery() {
       return new StringPair("?search=example", true);
   }

   // Adapted from ResultPair in the original UrlValidatorTest.
   private class StringPair {
       public String elem;
       public boolean valid;

       public StringPair(String elem, boolean valid) {
            this.elem = elem;
            this.valid = valid;
       }
   }
}
