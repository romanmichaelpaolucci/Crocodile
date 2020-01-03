#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <chrono>

class Crocodile
{
private:
  /* Data read from file */
  std::vector<std::vector<std::string>> data;
public:
/* Initialize the Crocodile class with a file */
  Crocodile(std::string filePath)
    {
    /* Read the file in using a file input stream */
    std::ifstream file(filePath);
    /* Initialize a matrix to return */
    std::vector<std::vector<std::string>> data;
    /* Initialize a row vector */
    std::vector<std::string> temps;
    /* Initialize a temporary string for storing the entire row */
    std::string temp;
    /* Initialize a temporary string to parse the stored row */
    std::string parser;
    /* While the file is readable */
    while(file.good())
    {
      /* Get the current line and store it to the variable temp */
      std::getline(file, temp);
      /* Treat the string as an input stream */
      std::istringstream iss(temp);
      /* While the string being treated as an input stream is readable */
      while(iss.good())
      {
        /* Parse at delimeter ','; Store in temporary variable parser */
        std::getline(iss, parser, ',');
        /* Add to the row vector */
        temps.push_back(parser);
      }
      /* After the row vector is constructed add it to the matrix */
      data.push_back(temps);
      /* We aren't passing by address so we can clear the row vector */
      temps.clear();
    }
    /* Done reading the file, close the stream */
    file.close();
    /* Set this instances data equal to the constructed matrix */
    this->data = data;
    }
    Crocodile(std::string filePath, int maxRows)
      {
        /* Read the file in using a file input stream */
        std::ifstream file(filePath);
        /* Initialize a matrix to return */
        std::vector<std::vector<std::string>> data;
        /* Initialize a row vector */
        std::vector<std::string> temps;
        /* Initialize a temporary string for storing the entire row */
        std::string temp;
        /* Initialize a temporary string to parse the stored row */
        std::string parser;
        /* Initialize an integer to count number of rows read */
        int r = 0;
        /* While the file is readable, and we haven't reached our bounds */
        while(file.good() && r < maxRows)
        {
          /* Get the current line and store it to the variable temp */
          std::getline(file, temp);
          /* Treat the string as an input stream */
          std::istringstream iss(temp);
          /* While the string being treated as an input stream is readable */
          while(iss.good())
          {
            /* Parse at delimeter ','; Store in temporary variable parser */
            std::getline(iss, parser, ',');
            /* Add to the row vector */
            temps.push_back(parser);
          }
          /* Increment the number of rows we have read */
          r++;
          /* After the row vector is constructed add it to the matrix */
          data.push_back(temps);
          /* We aren't passing by address so we can clear the row vector */
          temps.clear();
        }
        /* Done reading the file, close the stream */
        file.close();
        /* Set this instances data equal to the constructed matrix */
        this->data = data;
      }
/* Replace current file with a new one */
  void replaceFile(std::string filePath)
  {
    std::ifstream file(filePath);
    std::vector<std::vector<std::string>> data;
    std::vector<std::string> temps;
    std::string temp;
    std::string parser;
    while(file.good())
    {
      std::getline(file, temp);
      std::istringstream iss(temp);
      while(iss.good())
      {
        std::getline(iss, parser, ',');
        temps.push_back(parser);
      }
      data.push_back(temps);
      temps.clear();
    }
    file.close();
    this->data = data;
  }

  std::string getElement(unsigned int m, unsigned int n)
  {
    if(this->data.size() > 0)
      return data.at(m).at(n);
  }

  std::vector<std::string> getRow(unsigned int m)
  {
    return data.at(m);
  }

  std::string header(unsigned int x)
  {
    std::string temp = "";
    for(unsigned int i=0; i<x; i++)
    {
    for(std::string x : this->getRow(i))
      temp+=x+" ";
    temp+="\n";
    }
    return temp;
  }
  double mean(unsigned int column)
  {
    double temp = 0;
    for(unsigned int i=0;i<this->data.size();i++)
    {
      temp += atof(data.at(i).at(column).c_str());
    }
    return temp/data.size();
  }

};


int main()
{

  /* Timing Purposes */
  auto start = std::chrono::high_resolution_clock::now();


  Crocodile c("test.csv", 5);
  std::cout << c.header(5);


  /* Timing Purposes */
  auto stop = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
  std::cout << "Time taken by function: " << duration.count() << " microseconds" << std::endl;

  /*
  for(std::vector<std::string> x : readCSV("test.csv"))
  {
    for(std::string y : x)
    {
      std::cout << y << std::endl;
    }
  }
  */
  return 0;
}
