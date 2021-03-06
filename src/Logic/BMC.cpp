/**
 * \file BMC.cpp
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
 * \date   12 January 2015
 */

#include "BMC.h"


// =============================================================================
// run
//
// Compute a counterexample using BMC.
// F = pre^TF^notPost
//
// =============================================================================
void BMC::run(ProgramProfile *profile, Function *targetFun, YicesSolver *solver,
              Formula *TF, Formula *preCond, Formula *postCond,
              LoopInfoPass *loopInfo, Options *options) {
    
    // Add the trace formula to the context
    solver->init();
    solver->addToContext(TF);
    
    // Add all pre-condition (not negated)
    for (ExprPtr e : preCond->getExprs()) {
        e->setHard();
        solver->addToContext(e);
    }
    // Add all the not(post-condition) to the context
    for (ExprPtr e : postCond->getExprs()) {
        ExprPtr ne = Expression::mkNot(e);
        ne->setHard();
        solver->addToContext(ne);
    }
    
    // Compute BMC
    if (options->verbose()) {
        std::cout << "\n==============================================\n";
        std::cout << "Starting Bounded Model Checking...\n\n";
    }
        
    switch(solver->check()) {
        // Negated claim is satisfiable, i.e., does not hold
        case l_true: {
        } break;  
        // Negated claim is unsatisfiable: verification successful
        case l_false:
            return;
        case l_undef:
            std::cout << "unknown: it was not possible"; 
            std::cout << " to decide due to an incompleteness.\n";
            return;
    }    
    // Loops: check if the model make the CFG
    //        jump back to a loop header.
    bool propertyViolated = false;
    std::vector<BranchInst*> loopLatchBrs = loopInfo->getLoopLatchBrs();
    std::vector<BranchInst*>::iterator itb;
    for (itb=loopLatchBrs.begin(); itb!=loopLatchBrs.end(); ++itb) {
        BranchInst *I = *itb;
        Value *cond = I->getCondition();
        int val = solver->getBoolValue(cond->getName().str());
        BasicBlock *headerBB = loopInfo->getLoopLatch(I);
        BasicBlock *nextBB1 = I->getSuccessor(0);
        BasicBlock *nextBB2 = I->getSuccessor(1);
        if ((headerBB && headerBB==nextBB1 && val==l_true) 
            || (headerBB && headerBB==nextBB2 && val==l_false)) {
            unsigned line = 0;
            if (MDNode *N = I->getMetadata("dbg")) { 
                DILocation Loc(N); 
                line = Loc.getLineNumber();
            }            
            std::cout << "Violated property: unwinding assertion";
            std::cout << " (line " << line << ")\n";
            propertyViolated = true;
        }
    }
    if (propertyViolated) {
        exit(0);
    }

    ProgramTrace *E = new ProgramTrace(targetFun, FAIL);
    
    // Retrieve all main function arguments ,
    // retrieve their value from the model (of BMC)
    const FunctionType *FTy = targetFun->getFunctionType();
    Function::arg_iterator ait;
    for (ait = targetFun->arg_begin(); ait != targetFun->arg_end(); ++ait) {
        // Check the type of the argument
        const unsigned argNo = ait->getArgNo();
        const Type *argTy = FTy->getParamType(argNo);
        if (argTy->isIntegerTy() && !argTy->isIntegerTy(1)) {
            std::string argName = ait->getName().str();
            long value = solver->getValueOrZero(argName);
            Value *origin = ait;
            E->addProgramInput(origin, value);
        }
    }
    profile->addProgramTrace(E);
    
    solver->clean();
}
