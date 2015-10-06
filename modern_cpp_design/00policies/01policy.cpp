#include <iostream>
#include <fstream>
#include <string>

// host-class takes user-defined policy classes, each implementing a particular interface ("policy")
// and encapsulating some orthogonal aspect of the behavior of the instantiated host class
template<class OutputPolicy, class LanguagePolicy>
class HelloWorld : private OutputPolicy, private LanguagePolicy {
  private:
    using OutputPolicy::print;
    using LanguagePolicy::message;
  public:
    void run() const { print(message()); }
};

// output policy-classes
class OutputPolicyWriteToCout {
  protected:
    template<class MessageType>
    void print(const MessageType& message) const {std::cout << message << std::endl;}
};
class OutputPolicyWriteToFile {
  protected:
    template<class MessageType>
    void print(const MessageType& message) const {std::ofstream out("file.txt"); out << message << std::endl;}
};

// language policy-classes
class LanguagePolicyEnglish {
  protected:
    std::string message() const {return "Hello World!";}
};
class LanguagePolicyGerman {
  protected:
    std::string message() const {return "Hallo Welt!";}
};

int main() {
  typedef HelloWorld<OutputPolicyWriteToCout, LanguagePolicyEnglish> HelloWorldEnglish;
  typedef HelloWorld<OutputPolicyWriteToCout, LanguagePolicyGerman > HelloWorldGerman ;
  HelloWorldEnglish hw1;
  hw1.run();

  HelloWorldGerman  hw2;
  hw2.run();

  HelloWorld<OutputPolicyWriteToFile, LanguagePolicyGerman> hw3;
  hw3.run();
}
