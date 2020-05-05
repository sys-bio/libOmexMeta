/**
 * @file std_set.i
 * @brief Base file
 * @author DEVISER
 *
 * <!--------------------------------------------------------------------------
 * This file is part of libSBML. Please visit http://sbml.org for more
 * information about SBML, and the latest version of libSBML.
 *
 * Copyright (C) 2013-2016 jointly by the following organizations:
 * 1. California Institute of Technology, Pasadena, CA, USA
 * 2. EMBL European Bioinformatics Institute (EMBL-EBI), Hinxton, UK
 * 3. University of Heidelberg, Heidelberg, Germany
 *
 * Copyright (C) 2009-2013 jointly by the following organizations:
 * 1. California Institute of Technology, Pasadena, CA, USA
 * 2. EMBL European Bioinformatics Institute (EMBL-EBI), Hinxton, UK
 *
 * Copyright (C) 2006-2008 by the California Institute of Technology,
 * Pasadena, CA, USA
 *
 * Copyright (C) 2002-2005 jointly by the following organizations:
 * 1. California Institute of Technology, Pasadena, CA, USA
 * 2. Japan Science and Technology Agency, Japan
 *
 * This library is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published by the
 * Free Software Foundation. A copy of the license agreement is provided in the
 * file named "LICENSE.txt" included with this software distribution and also
 * available online as http://sbml.org/software/libsbml/license.html
 * ------------------------------------------------------------------------ -->
 */


/*=========================================================================

  Program: GDCM (Grassroots DICOM). A DICOM library

  Copyright (c) 2006-2011 Mathieu Malaterre
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
/* -----------------------------------------------------------------------------
 * std_set.i
 *
 * SWIG typemaps for std::set
 * ----------------------------------------------------------------------------- */

%include <std_common.i>

// ------------------------------------------------------------------------
// std::set
// ------------------------------------------------------------------------

%{
#include <set>
#include <algorithm>
#include <stdexcept>
%}

// exported class

namespace std {

    template< class V > class set {
        // add typemaps here
      public:
        typedef size_t size_type;
        typedef ptrdiff_t difference_type;
        typedef V value_type;
        set();
        set(const set< V > &);

        unsigned int size() const;
        bool empty() const;
        void clear();
        %extend {
            const V& get(const V& key) throw (std::out_of_range) {
                std::set< V >::iterator i = self->find(key);
                if (i != self->end())
                    return *i;
                else
                    throw std::out_of_range("key not found");
            }
            void insert(const V& key) { // Do NOT call this function 'set' !
                self->insert(key);
            }
            void del(const V& key) throw (std::out_of_range) {
                std::set< V >::iterator i = self->find(key);
                if (i != self->end())
                    self->erase(i);
                else
                    throw std::out_of_range("key not found");
            }
            bool has_key(const V& key) {
                std::set< V >::iterator i = self->find(key);
                return i != self->end();
            }
        }
    };

}
