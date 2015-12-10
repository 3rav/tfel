/*!
 * \file   StudyCurrentState.cxx
 * \brief    
 * \author THOMAS HELFER
 * \date   08 déc. 2015
 * \copyright Copyright (C) 2006-2014 CEA/DEN, EDF R&D. All rights 
 * reserved. 
 * This project is publicly released under either the GNU GPL Licence 
 * or the CECILL-A licence. A copy of thoses licences are delivered 
 * with the sources of TFEL. CEA or EDF may also distribute this 
 * project under specific licensing conditions. 
 */

#include<boost/python.hpp>
#include"MTest/StudyCurrentState.hxx"

void declareStudyCurrentState(void);

void declareStudyCurrentState(void)
{
  boost::python::class_<mtest::StudyCurrentState>("StudyCurrentState")
    ;

}
