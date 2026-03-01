# SOLID Principles — Examples in this Repository

TL;DR

This repository contains small Java examples that demonstrate SOLID design principles: Single Responsibility (SRP), Open/Closed (OCP), Liskov Substitution (LSP), Interface Segregation (ISP) and Dependency Inversion (DIP). The README below explains each principle, shows problem vs correct design (where applicable) and points to the source files under `src/main/java` for full examples.

Table of Contents

- Overview
- Single Responsibility Principle (SRP)
- Open/Closed Principle (OCP)
- Liskov Substitution Principle (LSP)
  - Violating example (tight coupling)
  - Correct design (loose coupling)
- Interface Segregation Principle (ISP)
  - Violating example
  - Correct design
- Dependency Inversion Principle (DIP)
  - Violating example
  - Correct design
- How to run
- Notes & Contributing

---

## Overview

SOLID is an acronym for five object-oriented design principles intended to make software designs more understandable, flexible and maintainable. This repository shows concise Java snippets demonstrating violations and corrected designs for a few of the principles so you can see the difference.

## Single Responsibility Principle (SRP)

A class should have only one reason to change — one responsibility. Keep classes focused and small. (This repo contains small classes; treat each example file as a focused responsibility.)

## Open/Closed Principle (OCP)

Software entities (classes, modules, functions) should be open for extension but closed for modification. Prefer adding new implementations or behaviors through extension (subclasses, strategies, decorators) rather than editing existing tested code.

## Liskov Substitution Principle (LSP)

A subtype must be substitutable for its base type without changing the correctness of the program. In other words, code using a base type must work correctly when given an instance of a derived type.

### Violating example (tight coupling)

See `src/main/java/com/tight/coupling/TightCouplingExample.java` and `src/main/java/com/tight/coupling/UserDatabase.java` for an example where a base/parent promises functionality (like `refund`) but a concrete child breaks that promise and throws an exception.

Short excerpt (conceptual):

```java
// Parent declared refund; some children don't support refund and may throw
class Payment {
    void pay(int amount) { /*...*/ }
    void refund(int amount) { /*...*/ }
}

class CashOnDelivery extends Payment {
    @Override
    void refund(int amount) {
        throw new RuntimeException("Refund not supported");
    }
}

// Upcasting causes runtime failure:
Payment p = new CashOnDelivery();
p.refund(1000); // crashes — LSP violated
```

### Correct design (loose coupling)

Split behaviors into smaller abstractions (e.g., `Payment` and `Refundable`) so that concrete classes only implement the capabilities they actually provide.

Relevant files: `src/main/java/com/loose/coupling/LooseCouplingExample.java` and related interfaces/implementations in `src/main/java/com/loose/coupling/` (for example `UserDataProvider`, `UserDatabaseProvider`, `WebServiceDataProvider`, `NewDatabaseProvider`).

Conceptual example:

```java
interface Payment { void pay(int amount); }
interface Refundable { void refund(int amount); }

class CreditCardPayment implements Payment, Refundable { /* ... */ }
class CashOnDelivery implements Payment { /* no refund implementation */ }
```

This keeps the promises of each abstraction clear and prevents substitutability failures.

## Interface Segregation Principle (ISP)

Clients should not be forced to depend on interfaces they do not use. Provide smaller, focused interfaces rather than large, catch-all interfaces.

### Violating example

```java
interface IVehicle { void drive(); void fly(); }

class Car implements IVehicle {
    public void drive() { /* ok */ }
    public void fly() { throw new UnsupportedOperationException(); }
}
```

The `Car` class is forced to implement `fly()` even though it doesn't support flying.

### Correct design

Split interfaces into `IDrive` and `IFly`. Let implementors mix only the capabilities they need.

```java
interface IDrive { void drive(); }
interface IFly { void fly(); }

class Car implements IDrive { public void drive() { /*...*/ } }
class FlyingCar implements IDrive, IFly { /*...*/ }
```

In this repository the `src/main/java/com/loose/coupling` examples show how smaller interfaces improve clarity.

## Dependency Inversion Principle (DIP)

High-level modules should not depend on low-level modules; both should depend on abstractions. Abstractions should not depend on details; details should depend on abstractions.

### Violating example

```java
class DataAccessLayer {
    void addCustomer(String name) {
        // ... add to DB ...
        FileLogger logger = new FileLogger(); // direct dependency on low-level concrete logger
        logger.log("Customer added " + name);
    }
}
```

`DataAccessLayer` depends on a concrete `FileLogger` — changing logging requires editing the high-level class.

### Correct design

Introduce an `ILogger` interface and inject the desired logger (constructor or setter). The high-level `DataAccessLayer` depends only on `ILogger`.

```java
interface ILogger { void log(String message); }
class FileLogger implements ILogger { public void log(String m) { /*...*/ } }

class DataAccessLayer {
    private final ILogger logger;
    public DataAccessLayer(ILogger logger) { this.logger = logger; }
    void addCustomer(String name) { logger.log("Customer added " + name); }
}
```

Files demonstrating dependency inversion examples: `src/main/java/com/loose/coupling/UserManager.java` and providers such as `NewDatabaseProvider.java`.

## How to run

This project uses Maven. From the repository root you can compile the code with:

```bash
mvn -q -DskipTests package
```

You can run specific example classes with `java -cp target/classes com.example.YourExample` or use your IDE to run main classes found in `src/main/java` (for example `car.example.bean.App`).

## Notes & Contributing

- The code in this repo is intentionally minimal and focused on demonstrating design principles — it is not production-ready.
- If you want additional examples (SRP and OCP concrete snippets), open an issue or submit a PR with the expanded examples and unit tests.

---

License: feel free to reuse these examples for learning and demos.

