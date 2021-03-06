package momfo.problems.singletask;

import java.io.IOException;

import jmetal.core.Problem;
import jmetal.core.Solution;
import jmetal.core.Variable;
import jmetal.encodings.solutionType.BinaryRealSolutionType;
import jmetal.encodings.solutionType.RealSolutionType;
import jmetal.util.JMException;
import momfo.problems.core.GFunctions;
import momfo.problems.core.IO;

public class NIMS2 extends Problem {
	double[][] mnm2;
	
	public NIMS2(String solutionType) throws IOException {
		numberOfVariables_ = 20;
		numberOfObjectives_ = 2;
		numberOfConstraints_ = 0;
		problemName_ = "NIMS2";

		lowerLimit_ = new double[numberOfVariables_];
		upperLimit_ = new double[numberOfVariables_];
		
		
		lowerLimit_[0] = lowerLimit_[1] = 0;
		upperLimit_[0] = upperLimit_[1] = 1;
		
		for (int i = 2; i < numberOfVariables_; i++) {
			lowerLimit_[i] = -20;
			upperLimit_[i] = 20;
		}

		mnm2 = IO.readRotationMatrix("Mdata/M_NIMS_2.txt");
		
		if (solutionType.compareTo("BinaryReal") == 0)
			solutionType_ = new BinaryRealSolutionType(this);
		else if (solutionType.compareTo("Real") == 0)
			solutionType_ = new RealSolutionType(this);
		else {
			System.out.println("Error: solution type " + solutionType + " invalid");
			System.exit(-1);
		}
	} // NIHS1
	
	
	@Override
	public void evaluate(Solution solution) throws JMException {
		Variable[] decisionVariables = solution.getDecisionVariables();

		double[] f = new double[numberOfObjectives_]; 
		double[] x = new double[numberOfVariables_]; 

		for (int i = 0; i < numberOfVariables_; i++)
			x[i] = decisionVariables[i].getValue();
		
		double[] z = new double[numberOfVariables_ - 2];
		for (int i = 0; i < numberOfVariables_ - 2; i++) {
			double sum = 0;
			for (int j = 0; j < numberOfVariables_ - 2; j++) 
				sum += mnm2[i][j] * (x[j + 2]);
			z[i] = sum;
		}
		
		double q = GFunctions.getSphere(z, 0, z.length - 1);
		
		f[0] = 0.5 * (x[0] + x[1]);
		f[1] = q * (1 - (f[0] / q) * (f[0] / q));
		
		solution.setObjective(0, f[0]);
		solution.setObjective(1, f[1]);
	}

}
