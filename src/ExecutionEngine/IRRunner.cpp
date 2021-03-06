/**
 * \file IRRunner.cpp
 *
 * ----------------------------------------------------------------------
 *                SNIPER : Automatic Fault Localization 
 *
 * Copyright (C) 2016 Si-Mohamed LAMRAOUI
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program (see LICENSE.TXT).  
 * If not, see <http://www.gnu.org/licenses/>.
 * ----------------------------------------------------------------------
 *
 * \author Si-Mohamed Lamraoui
 * \date   28 February 2016
 */

#include "IRRunner.h"

void IRRunner::run(ProgramProfile *profile, LocalVariables *locVars,
                    LoopInfoPass *loopInfo) {
    // Init
    EE = initialize();
    Executor::init(loopInfo, profile, 
                   /*collectBlocks*/ options->htfUsed(),
                   /* desactivate symbolic execution */ true,
                   /* no assert */ true);
    // Execute the program for each input list
    int i = 0;
    for (std::vector<Value*> IV : inputValuesVec) {
        assert(!IV.empty() && "Empty input values list!");
        // Prepare the executor
        VariablesPtr inputs = std::make_shared<Variables>();
        Function::arg_iterator ait = targetFun->arg_begin();
        for (Value *v : IV) {
            ConstantInt *ci = dyn_cast<ConstantInt>(v);
            assert(ci && "No concrete value for variable!");
            int val = (int) ci->getSExtValue();
            inputs->add(ait++, val);
        }
        Executor::start(targetFun, inputs, locVars);
        // Call the function f with the input values as argument
        Value *output = callFunction(EE, llvmMod, targetFun, IV);
        // Get the expected output (if any)
        Value *expectedOutput = NULL;
        if (!outputValuesVec.empty()) {
            expectedOutput = outputValuesVec[i++];
        } else {
            std::cout << "WARNING!!!\n";
        }
        // If an expected ouput is provided,
        // we use it to determine the result
        if (expectedOutput && output) {
            ConstantInt *O = dyn_cast<ConstantInt>(output);
            ConstantInt *EO = dyn_cast<ConstantInt>(expectedOutput);
            assert((O && EO) && "No concrete value for variables!");
            int oval = (int) O->getSExtValue();
            int eoval  = (int) EO->getSExtValue();
            if (oval==eoval) {
                Executor::Trace->setSuccessful();
            } else {
                Executor::Trace->setFailing();
                Executor::Trace->setExpectedOutput(expectedOutput);
            }
        } else {
            Executor::Trace->setUnknow();
        }
        // Check if there were pointer incompleteness
        if(!Executor::areAllLocDefinite()) {
            std::cout << "warning: pointer incompleteness!" << std::endl;
        }
        // Next round
        Executor::endOfRun();
    }
    if (options->dbgMsg()) {
        std::cout << "\n=== [IR Runner] terminated ===\n";
        profile->dump();
    }
    // Cleaning
    Executor::clean();    
}

std::vector<std::vector<Value*> > IRRunner::parseTestsuiteFile(
                                const std::string &filename) {
    std::ifstream infile(filename.c_str());
    assert(infile && "Cannot open the testsuite file!");
    std::string line;
    std::vector< std::vector<int> > all_integers;
    while ( getline( infile, line ) ) {
        std::istringstream is( line );
        all_integers.push_back(
        std::vector<int>( std::istream_iterator<int>(is),
        std::istream_iterator<int>() ) );
    }
    LLVMContext &context = getGlobalContext();
    IRBuilder<> IRB(context);
    std::vector<std::vector<Value*> > TS;
    for(std::vector<int> line_ints : all_integers) {
        std::vector<Value*> TC;
        for (int val : line_ints) {
            Value *V = IRB.getInt32(val);
            TC.push_back(V);
        }
        TS.push_back(TC);
    }
    if (options->dbgMsg()) {
        std::cout << TS.size() << " testcase(s) loaded.\n";
    }
    return TS;
}

std::vector<Value*> IRRunner::parseGoldenOutputsFile(const std::string &filename) {
    // Open the file
    std::ifstream infile(filename.c_str());
    assert(infile && "Cannot open the golden outputs file.");
    // Read the elements in the file into a vector
    std::vector<int> allValues;
    int value;
    while ( infile >> value ) {
        allValues.push_back(value);
    }
    // Convert the integers into llvm values
    LLVMContext &context = getGlobalContext();
    IRBuilder<> IRB(context);
    std::vector<Value*> GO;
    for (int val : allValues) {
        Value *V = IRB.getInt32(val);
        GO.push_back(V);
    }
    if (options->dbgMsg()) {
        std::cout << GO.size() << " testcase(s) loaded.\n";
    }
    return GO;
}
