# Dining Philosophers Problem

The Dining Philosophers Problem is a classic synchronization problem in computer science, illustrating the challenges of allocating shared resources without causing deadlock or starvation. This project provides an implementation of the Dining Philosophers Problem to demonstrate and solve these issues using various synchronization techniques.

  ![Dining Philosophers](https://sphof.readthedocs.io/_images/philtable.png)

## Introduction

The Dining Philosophers Problem was originally formulated by Edsger Dijkstra in 1965. The problem describes five philosophers sitting around a circular table, alternating between thinking and eating. Each philosopher needs two forks to eat, but there are only five forks on the table. The challenge is to design a protocol that ensures no philosopher will starve and prevents deadlock.

## Problem Description

### Scenario

- Five philosophers sit around a table.
- Each philosopher alternates between thinking and eating.
- A fork is placed between each pair of adjacent philosophers.
- To eat, a philosopher needs to pick up both the fork to their left and the fork to their right.
- Philosophers can only pick up one fork at a time and must put down both forks after eating.

### Objectives

1. **Prevent Deadlock**: Ensure that no circular wait condition causes all philosophers to be stuck waiting for forks.
2. **Avoid Starvation**: Ensure that every philosopher gets a chance to eat.

## Implementation

Our implementation of the Dining Philosophers Problem explores various synchronization techniques to solve the problem:

- **Mutex Locks**: Use mutex locks to control access to the forks.
- **Semaphore**: Implement a semaphore-based solution to manage resource allocation.
- **Monitors**: Use monitors to encapsulate the synchronization logic.
- **Chandy/Misra Solution**: Implement the Chandy/Misra solution which is a distributed solution to avoid deadlock.

## Features

- **Multiple Synchronization Strategies**: Compare and contrast different approaches to solve the problem.
- **Configurable Philosophers**: Adjust the number of philosophers and forks to test the implementation.
- **Visualization**: Visualize the state of each philosopher and the forks to better understand the dynamics of the problem.

## Contact

For any questions, feedback, or support, please contact us at (taoussi.aimen@gmail.com) Or Contact me in My github (https://github.com/REDX-at).

---

Thank you for exploring the Dining Philosophers Problem with us!
