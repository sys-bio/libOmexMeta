//
// Created by Ciaran on 5/20/2020.
//

#ifndef LIBSEMSIM_HERE_H
#define LIBSEMSIM_HERE_H
// macro helpful for debugging
#define HERE()                              \
do {                                        \
  std::cout << __FILE__ << ":" << __LINE__ << std::endl; \
} while (0)

#endif //LIBSEMSIM_HERE_H
