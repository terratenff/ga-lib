#include <iostream>
#include <vector>
#include <algorithm>
#include "ga.h"
#include "population.h"
#include "nullcrossover.h"
#include "nullmutation.h"
#include "tspsolution.h"
#include "tspevaluator.h"
#include "tspdata.h"
#include "tspresult.h"
#include "multithreading/gamultithreaded.h"
#include "random_number_generators/rngmt.h"
#include "random_number_generators/rngknuth.h"
#include "population_initializers/tspinitializerrandom.h"
#include "selectors/tspselectortournament.h"
#include "selectors/tspselectorroulettewheel.h"
#include "crossover_operators/tspcrossoveronepoint.h"
#include "crossover_operators/tspcrossoverorder.h"
#include "mutation_operators/tspmutationswap.h"
#include "mutation_operators/tspmutationnearestneighbor.h"
#include "mutation_operators/tspmutationsequenceinversion.h"
#include "mutation_operators/tspmutationsequencerelocation.h"
#include "mutation_operators/tspmutationsequenceshuffle.h"
#include "post_generation_operators/tsppgoduplicatereplacer.h"
#include "post_generation_operators/tsppgoretention.h"
#include "post_generation_operators/tsppgofiltration.h"
#include "post_generation_operators/tsppgoelitism.h"

int main()
{
    // Create components necessary for the GA instance.
    //RNGMT* rng = new RNGMT(1);
    //RNGKNUTH* rng = new RNGKNUTH(1);
    TSPData* data = new TSPData("sample_matrix.txt");
    TSPEvaluator* evaluator = new TSPEvaluator(data);
    TerminationCriteria* criteria = new TerminationCriteria(2000, 10000, 1, 30, -999999, 999999);
    TSPInitializerRandom* initializer1 = new TSPInitializerRandom(data, evaluator, 1);
    TSPSelectorTournament* selector1 = new TSPSelectorTournament(10, 1, 0.90);
    TSPSelectorRouletteWheel* selector2 = new TSPSelectorRouletteWheel(10, 1);
    NullCrossover* crossoverOperator1 = new NullCrossover(data, evaluator, 10);
    TSPCrossoverOnePoint* crossoverOperator2 = new TSPCrossoverOnePoint(data, evaluator, 45);
    TSPCrossoverOrder* crossoverOperator3 = new TSPCrossoverOrder(data, evaluator, 45);
    NullMutation* mutationOperator1 = new NullMutation(data, evaluator, 90);
    TSPMutationSwap* mutationOperator2 = new TSPMutationSwap(data, evaluator, 2, 100);
    TSPMutationNearestNeighbor* mutationOperator3 = new TSPMutationNearestNeighbor(data, evaluator, 2);
    TSPMutationSequenceInversion* mutationOperator4 = new TSPMutationSequenceInversion(data, evaluator, 2, 50, 10);
    TSPMutationSequenceRelocation* mutationOperator5 = new TSPMutationSequenceRelocation(data, evaluator, 2, 10, 2);
    TSPMutationSequenceShuffle* mutationOperator6 = new TSPMutationSequenceShuffle(data, evaluator, 2, 25, 5);
    TSPPGODuplicateReplacer* pgOperator1 = new TSPPGODuplicateReplacer(data, evaluator, 10, initializer1);
    TSPPGORetention* pgOperator2 = new TSPPGORetention(data, evaluator, 10, 0.10f);
    TSPPGOFiltration* pgOperator3 = new TSPPGOFiltration(data, evaluator, 50, initializer1);
    TSPPGOElitism* pgOperator4 = new TSPPGOElitism(data, evaluator, 10, 0.05f);

    // Create and configure the GA instance.
    GA ga;
    //GAMultithreaded ga;
    //ga.setThreadCount(4);
    ga.setPopulationSize(100);
    ga.setSortOrder(false);
    //ga.setPrintFrequency(0);
    //ga.setRandomNumberGenerator(rng);
    ga.setProblemData(data);
    ga.setEvaluator(evaluator);
    ga.setTerminationCriteria(criteria);
    ga.addPopulationInitializer(initializer1);
    ga.addSelector(selector1);
    ga.addSelector(selector2);
    ga.addCrossoverOperator(crossoverOperator1);
    ga.addCrossoverOperator(crossoverOperator2);
    ga.addCrossoverOperator(crossoverOperator3);
    ga.addMutationOperator(mutationOperator1);
    ga.addMutationOperator(mutationOperator2);
    ga.addMutationOperator(mutationOperator3);
    ga.addMutationOperator(mutationOperator4);
    ga.addMutationOperator(mutationOperator5);
    ga.addMutationOperator(mutationOperator6);
    ga.addPostGenerationOperator(pgOperator1);
    ga.addPostGenerationOperator(pgOperator2);
    ga.addPostGenerationOperator(pgOperator3);
    ga.addPostGenerationOperator(pgOperator4);

    // Start the algorithm.
    ga.run();
    ga.print();

    // Create, display and save results.
    /*
    Solution* solution = ga.getBestSolution();
    int terminationCode = ga.getTerminationCode();
    unsigned int generation = ga.getTotalGeneration();
    long double time = ga.getTotalTime();

    ResultData* results = new TSPResult(solution, time, generation, terminationCode);
    results->print();
    results->save("results.txt");
    delete results;
    */
}

