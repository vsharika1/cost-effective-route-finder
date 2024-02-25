#include<iostream>
#include<fstream>
#include<cassert>
#include<ctime>
#include<iomanip>
using namespace std;
 
class CMPT135_String
{
private:
    char *buffer; //The dynamic array to store the printable characters and a null terminating character
public:
    CMPT135_String(); //The buffer is initialized to nullptr value
    CMPT135_String(const char *); //A non-default constructor with a null terminated char array argument
    CMPT135_String(const CMPT135_String &); //Deep copy constructor
    ~CMPT135_String();  //Delete any heap memory and assign buffer nullptr value
    CMPT135_String& operator = (const CMPT135_String &); //Memory cleanup and deep copy assignment
    int length() const; //Return the number of printable characters. Return zero if buffer is nullptr
    bool empty() const;  //Return true if length is 0. Otherwise return false
    char& operator [] (const int &) const;  //Assert index and then return the char at the index
    CMPT135_String operator + (const char &) const; //See assignment 1
    CMPT135_String& operator += (const char &); //See assignment 1
    bool operator == (const CMPT135_String &) const; //See assignment 1
    bool operator != (const CMPT135_String &) const; //See assignment 1
    friend istream& operator >> (istream &, CMPT135_String &); //Implemented for you
    friend ostream& operator << (ostream &, const CMPT135_String &); //Implemented for you
};
CMPT135_String::CMPT135_String() : buffer(nullptr) {}
CMPT135_String::CMPT135_String(const char *C)
{
    if(C == nullptr)
    {
        buffer=nullptr;
        return;
    }
    int length = 0;
    while(C[length] != '\0')
        length++;
    if(length == 0)
        buffer = nullptr;
    else
    {
        buffer = new char[length + 1];
        for (int i = 0; i < length; i++)
            buffer[i] = C[i];
        buffer[length] = '\0';
    }
}
CMPT135_String::CMPT135_String(const CMPT135_String &C)
{
    int length = C.length();
    buffer = new char[length + 1];
    for(int i = 0; i < length; i++)
    {
        buffer[i] = C[i];
    }
    buffer[length] = '\0';
}
CMPT135_String::~CMPT135_String()
{
    if(buffer != nullptr)
    {
        delete [] buffer;
        buffer = nullptr;
    }
}
CMPT135_String& CMPT135_String::operator = (const CMPT135_String &C)
{
    int length = C.length();
    buffer = new char[length + 1];
    for(int i = 0; i < length; i++)
    {
        buffer[i] = C[i];
    }
    buffer[length] = '\0';
    return *this;
}
int CMPT135_String::length() const
{
    if(buffer == nullptr)
        return 0;
    int length = 0;
    while(buffer[length] != '\0')
        length++;
    return length;
}
bool CMPT135_String::empty() const
{
    int length = this->length();
    if(length == 0)
        return true;
    else
        return false;
}
char& CMPT135_String::operator [] (const int &index) const
{
    assert(index >= 0 && index < this->length());
    return buffer[index];
}
CMPT135_String CMPT135_String::operator + (const char &C) const
{
    int length = this->length();
    CMPT135_String temp;
    temp.buffer = new char[length + 2];
    for(int i = 0; i < length; i++)
    {
        temp.buffer[i] = this->buffer[i];
    }
    temp.buffer[length] = C;
    temp.buffer[length + 1] = '\0';
    return temp;
}
CMPT135_String& CMPT135_String::operator += (const char &C)
{
    (*this) = (*this) + C;
    return (*this);
}
bool CMPT135_String::operator == (const CMPT135_String &C) const
{
    int length = this->length();
    if (length != C.length())
        return false;
    else
    {
        for(int i = 0; i < length; i++)
        {
            if(buffer[i] != C[i])
                return false;
        }
        return true;
    }
}
bool CMPT135_String::operator != (const CMPT135_String &C) const
{
   if(*this == C)
       return false;
   else
       return true;
}
istream& operator >> (istream &in, CMPT135_String &s)
{
    //This function reads characters input from a keyboard or a file until either a TAB, EOL, or EOF is
    //reached. The function ignores any leading or trailing spaces. It is designed to be able to read a
    //string of characters that may or may not contain spaces without any problem.
 
    //Define some useful constant values
    #define SPACE ' '
    #define TAB '\t'
    #define EOL    '\n'
 
    //Delete the old value of s
    s.~CMPT135_String();
 
    //Skip leading spaces, tabs, and empty lines
    char ch;
    while (!in.eof())
    {
        in.get(ch);
        if (ch == SPACE || ch == TAB || ch == EOL)
            continue;
        break;
    }
 
    //Append the value in ch to s
    if (ch != SPACE && ch != TAB && ch != EOL)
        s += ch;
 
    //Read characters into s until a TAB or EOL or EOF is reached
    while (!in.eof())
    {
        in.get(ch);
        if (ch == TAB || ch == EOL || in.eof())
            break;
        else
            s += ch;
    }
 
    //Remove any trailing spaces
    int trailingSpacesCount = 0;
    for (int i = s.length()-1; i >= 0; i--)
    {
        if (s[i] != SPACE)
            break;
        trailingSpacesCount++;
    }
    CMPT135_String temp;
    for (int i = 0; i < s.length()-trailingSpacesCount; i++)
        temp += s[i];
    s = temp;
 
    return in;
}
ostream& operator << (ostream &out, const CMPT135_String &s)
{
    for (int i = 0; i < s.length(); i++)
        out << s[i];
    return out;
}
 
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <class T>
class SmarterArray
{
private:
    T *A; //The dynamic array to store the elements
    int size; //The number of elements in the array
 
public:
    //Constructors
    SmarterArray(); //Implemented for you
    SmarterArray(const T*, const int&); //Deep copy of the argument dynamic array with the given size
    SmarterArray(const SmarterArray<T>&); //Deep copy of the argument
 
    //Assignment operator
    SmarterArray<T>& operator = (const SmarterArray<T>&); //Memory cleanup and deep copy of the argument
 
    //Destructor
    ~SmarterArray(); //Memory cleanup and resetting the size
 
    //Getters, Setters, operators and other functions
    int getSize() const; //Return the number of elements in the container
    T& operator[](const int&) const; //Assert index and then return the element at the given index
    int find(const T&) const; //Return the index of the first element that is == to the argument.
                                //Return -1 if not found.
    void append(const T&);  //Store the argument value after the last element
    void insert(const int &, const T&); //Assert the integer argument index >= 0 && index <= size and then
                                        //Insert the T type argument into the calling object at the index.
                                        //If the index argument is equal to size, then perform append
    bool remove(const int&); //If the index is valid, then remove the element at the index argument
                            //from the calling object and return true. Otherwise do nothing and return
                            //false. Do not assert the index argument.
    bool operator == (const SmarterArray<T>&) const; //Return true if sizes are equal and elements at the
                                                        //same indexes are equal. Otherwise return false
   
    template <class T1> //Those of you working with xCode, don't use the same template name T. T1 is ok.
    friend ostream& operator << (ostream&, const SmarterArray<T1>&); //Implemented for you
};
template <class T>
SmarterArray<T>::SmarterArray()
{
    this->A = nullptr;
    this->size = 0;
}
template <class T>
SmarterArray<T>::SmarterArray(const T* A, const int& size)
{
    if(size > 0)
    {
        this->size = size;
        this->A = new T[this->size];
        for(int i = 0; i < this->size; i++)
            this->A[i] = A[i];
    }
    else
        this->size = 0;
}
template <class T>
SmarterArray<T>::SmarterArray(const SmarterArray<T>& S)
{
    this->size = S.getSize();
    if(this->size > 0)
    {
        this->A = new T[this->size];
        for(int i = 0; i < this->size; i++)
            this->A[i] = S[i];
    }
}
 
template <class T>
SmarterArray<T>& SmarterArray<T>::operator = (const SmarterArray<T>& S)
{
    if(this == &S)
        return *this;
    this->~SmarterArray();
    this->size = S.getSize();
    if(this->size > 0)
    {
        this->A = new T[S.getSize()];
        for(int i = 0; i < S.getSize(); i++)
            this->A[i] = S[i];
    }
    return *this;
}
 
template <class T>
SmarterArray<T>::~SmarterArray()
{
    if(this->getSize() > 0)
    {
        delete [] this->A;
        this->size = 0;
        A = nullptr;
    }
}
 
template <class T>
int SmarterArray<T>::getSize() const
{
    return this->size;
}
template <class T>
T& SmarterArray<T>::operator[](const int &index) const
{
    assert(index >= 0 && index < this->size);
    return this->A[index];
}
template <class T>
int SmarterArray<T>::find(const T& value) const
{
    for(int i = 0; i < this->size; i++)
        if(this->A[i] == value)
            return i;
    return -1;
}
template <class T>
void SmarterArray<T>::append(const T& value)
{
    T *temp = new T[this->size + 1];
    for(int i = 0; i < this->size; i++)
        temp[i] = this->A[i];
    temp[this->size] = value;
    if(this->size > 0)
        delete [] this->A;
    this->A = temp;
    this->size += 1;
}
template <class T>
void SmarterArray<T>::insert(const int &index, const T& value)
{
    assert(index >= 0 && index <= this->size);
    if(index == size)
        append(value);
    else
    {
        T *temp = new T[this->size + 1];
        for(int i = 0; i < index; i++)
        {
            temp[i] = this->A[i];
        }
        temp[index] = value;
        for(int i = index + 1; i < this->size + 1; i++)
        {
            temp[i] = this->A[i - 1];
        }
        delete [] this->A;
        this->A = temp;
        size = size + 1;
    }
}
template <class T>
bool SmarterArray<T>::remove(const int& index)
{
    if(index < 0 || index >= this->size)
        return false;
    else
    {
        T *temp;
        if(size - 1 > 0)
            temp = new T[size - 1];
      
        for(int i = 0; i < index; i++)
            temp[i] = this->A[i];
        for(int i = index + 1; i < size; i++)
            temp[i - 1] = this->A[i];
      
        delete [] this->A;
        if(size - 1 > 0)
            this->A = temp;
        else
            this->A = nullptr;
        size = size - 1;
        return true;
    }
}
template <class T>
bool SmarterArray<T>::operator == (const SmarterArray<T>& S) const
{
    if(S.getSize() != this->size)
        return false;
    else
    {
        int count = 0;
        for(int i = 0; i < this->size; i++)
        {
            if(S.A[i] == this->A[i])
            count++;
        }
        if(count==this->size)
            return true;
        else
            return false;
    }
}
 
template <class T>
ostream& operator << (ostream& out, const SmarterArray<T>& L)
{
    if (L.getSize() == 0)
        out << "[Empty List]";
    else
    {
        for (int i = 0; i < L.getSize()-1; i++)
            out << L[i] << endl;
        out << L[L.getSize()-1] << endl;
    }
    return out;
}
 
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct Edge
{
    int desVertexIndex; //the index (in the underlying graph) of the destination vertex of this edge
    double cost; //cost of an edge
};
 
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Vertex
{
private:
    CMPT135_String name; //Name of the city at the vertex
    SmarterArray<Edge> E; //A container to store the edges emanating from this vertex. All the elements of
             //E have the same origin vertex which is the this object. But they have different destination
             //vertices which are given by the desVertexIndex member variable of each element
 
public:
    Vertex(); //Assign name = "N/A" and initialize E to an empty container (default object E)
    Vertex(const CMPT135_String &); //Assign name = the argument and initialize E to an empty container
    CMPT135_String getName() const; //Return the name
    SmarterArray<Edge> getEdgeSet() const; //Return E
    int getEdgeSetSize() const; //Return the size of E
    Edge getEdge(const int & desVertexIndex) const; //Assert an edge whose destination vertex index is
                                                //equal to the argument is found in E. Then return the edge
    double getEdgeCost(const int &desVertexIndex) const; //Assert an edge whose destination vertex index
                                            //is equal to the argument is found in E. Then return its cost
    void appendEdge(const int &desVertexIndex, const double &cost); //Assert there is no element of E
                //whose destination vertex index and cost are equal to the argument values. Then append
                //a new element whose destination vertex index and cost are initialized with the
                //argument values to E
    friend ostream& operator << (ostream &, const Vertex &); //Implemented for you
};
Vertex::Vertex() : name("N/A"), E(SmarterArray<Edge>()) {}
Vertex::Vertex(const CMPT135_String &S)
{
    this->name = S;
    this->E = SmarterArray<Edge>();
}
CMPT135_String Vertex::getName() const { return this->name; }
SmarterArray<Edge> Vertex::getEdgeSet() const { return this->E; }
int Vertex::getEdgeSetSize() const { return this->E.getSize(); }
Edge Vertex::getEdge(const int & desVertexIndex) const
{
    assert(desVertexIndex >= 0 && desVertexIndex < this->E.getSize());
    return this->E[desVertexIndex];
}
double Vertex::getEdgeCost(const int &desVertexIndex) const
{
    assert(desVertexIndex >= 0 && desVertexIndex < this->E.getSize());
    return this->E[desVertexIndex].cost;
}
void Vertex::appendEdge(const int &desVertexIndex, const double &cost)
{
    int count = 0;
    for(int i = 0; i < this->getEdgeSetSize(); i++)
        if((E[i].cost == cost) && (E[i].desVertexIndex == desVertexIndex))
            count++;
    assert(count == 0);
    Edge edge;
    edge.cost = cost;
    edge.desVertexIndex = desVertexIndex;
    E.append(edge);
}
ostream& operator << (ostream &out, const Vertex &vertex)
{
    out << "Name = " << vertex.name << endl;
    out << "Edge Set" << endl;
    for (int i = 0; i < vertex.E.getSize(); i++)
        out << "\t to ---> " << vertex.E[i].desVertexIndex << ", cost = " << vertex.E[i].cost << endl;
    return out;
}
 
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Graph
{
private:
    SmarterArray<Vertex> V;
public:
    Graph();//Construct empty graph (default object V)
    Graph(const char *); //Construct a graph from a text file whose path is given by the argument cstring.
        //The input text file will consist a pair of cities and the cost to go from one to the other on
        //every line. The pair of cities and their cost will be separated by one or more SPACE or TAB
        //characters. It doesn't matter how many spaces or tabs are present. BUT THERE HAS TO BE AT LEAST
        //ONE TAB CHARACTER between the pairs of cities and AT LEAST ONE TAB between the second city and
        //the cost. This is because the CMPT135_String class uses TAB as a deliminator (separator). This
        //means city names can be made up of one or more words separated by spaces. An example of one line
        //of text in the input text file is:
        //        New Westminster             Port Coquitlam        4.5
        //In this example, there has to be at least one TAB char between "New Westminster" and "Port
        //Coquitlam" and at least one TAB character between "Port Coquitlam" and 4.5. Of course there can
        //be more than one TAB characters. The number of TABs between the cities names and the second city
        //and the cost can be equal or different. There can also be zero or more spaces as much as you
        //like without causing any problem. Moreover there can be as many empty lines as one likes at the
        //end of the file. However there MUST NOT BE any empty line before the line that consists of the
        //last pair of cites and their cost.
        /*
        Thus this function should perform the following tasks
1.    Construct a non-default file input streaming object using the cstring argument file name
2.    Assert the file is opened successfully
3.    While EOF is not reached do
a.    Read city name. This is the departure city. (fin >> departure;)
b.    If departure city is empty CMPT135_String object, then break.
c.    Read city name. This is the destination city. (fin >> destination;)
d.    Read the cost (double data type)
e.    Append a new vertex whose name is the departure city and whose edge set is empty to the this object. You must use the appendVertex member function of this class (see below) to append appropriately.
f.    Append a new vertex whose name is the destination city and whose edge set is empty to the this object. You must use the appendVertex member function of this class to append appropriately.
g.    Append a new edge from the departure city to the destination city with a cost read in part (d) above to the this object. You must use the appendEdge member function of this class (see below) to append appropriately.
h.    Append a new edge from the destination city to the departure city with a cost read in part (d) above to the this object. You must use the appendEdge member function of this class (see below) to append appropriately.
4.    Close the input file stream object and you are done.
        */
    SmarterArray<Vertex> getVertexSet() const; //Return V
    int getVertexSetSize() const; //Return the number of elements of V
    Vertex getVertex(const int &) const; //Assert the index argument and then return the element at index
    int getVertexIndex(const CMPT135_String &) const; //Return the index of an element whose name matches                                                        //the argument. If no such element is found, return -1
                                                    //Assertion should not be performed.
    int getVertexIndex(const Vertex &) const; //Return the index of the element whose name matches the
                                            //name of the vertex argument. If no such element is found,
                                            //return -1. Assertion should not be performed.
    CMPT135_String getRandomVertexName() const; //Pick a vertex at random and return its name
    void appendVertex(const Vertex &); //Append the argument only if no such vertex already exists in the
                                        // calling object. If same name vertex already exists then do nothing
                                        //and return. Assertion should not be performed.
    void appendVertex(const CMPT135_String &); //Append a new vertex with the given name and empty E only
                           //if no such vertex already exists in the calling object. If same name vertex
                            //already exists then do nothing and return. Assertion should not be performed.
 
 
    void appendEdge(const CMPT135_String &dep, const CMPT135_String &des, const double &cost); //Assert
//two vertices whose names match the arguments exist. Then append an edge to the vertex whose name matches
//the dep argument. The destination vertex index of the edge must be set to the index of the vertex whose
//name matches des and its cost must be set to the cost argument
    friend ostream& operator << (ostream &, const Graph &); //Implemented for you
};
Graph::Graph() : V(SmarterArray<Vertex>()) {}
Graph::Graph(const char * file)
{
    ifstream fin;
    fin.open(file);
   
    assert(fin.fail() == false);
   
    CMPT135_String departure, destination;
    double travelCost;
   
    while(fin.eof() == false)
    {
        fin >> departure;
        if(departure.empty())
            break;
        fin >> destination;
        fin >> travelCost;
        appendVertex(departure);
        appendVertex(destination);
        appendEdge(departure, destination, travelCost);
        appendEdge(destination, departure, travelCost);
    }
    fin.close();
}
SmarterArray<Vertex> Graph::getVertexSet() const { return this->V; }
int Graph::getVertexSetSize() const { return this->V.getSize(); }
Vertex Graph::getVertex(const int &index) const
{
    assert(index >= 0 && index < this->V.getSize());
    return this->V[index];
}
int Graph::getVertexIndex(const CMPT135_String &S) const
{
    for(int i = 0; i < this->getVertexSetSize(); i++)
    {
        if(S == this->V[i].getName())
            return i;
    }
    return -1;
}
int Graph::getVertexIndex(const Vertex &vertex) const
{
    for(int i = 0; i < this->getVertexSetSize(); i++)
    {
        if(V[i].getName() == vertex.getName())
            return i;
    }
    return -1;
}
CMPT135_String Graph::getRandomVertexName() const
{
    int index = rand() % (V.getSize() - 1);
    return V[index].getName();
}
void Graph::appendVertex(const Vertex &vertex)
{
    for(int i = 0; i < V.getSize(); i++)
    {
        if(V[i].getName() == vertex.getName())
            return;
    }
    V.append(vertex);
}
void Graph::appendVertex(const CMPT135_String &S)
{
    for(int i = 0; i < V.getSize(); i++)
    {
        if(V[i].getName() == S)
        return;
    }
    Vertex vertex(S);
    V.append(vertex);
}
void Graph::appendEdge(const CMPT135_String &dep, const CMPT135_String &des, const double &cost)
{
    int count = 0;
    for(int i = 0; i < V.getSize(); i++)
        if(V[i].getName() == dep)
            count++;
    for(int i = 0; i < V.getSize(); i++)
        if(V[i].getName() == des)
            count++;
    assert(count == 2);
    int index;
    for(int i = 0; i < V.getSize(); i++)
    {
        if(V[i].getName() == des)
        {
            index = i;
            break;
        }
    }
    for(int i = 0; i < V.getSize(); i++)
    {
        if(V[i].getName() == dep)
        {
            V[i].appendEdge(index, cost);
        }
    }
}
ostream& operator << (ostream &out, const Graph &g)
{
    const int CITY_NAME_WIDTH = 25;
    out << endl;
    out << "The graph has " << g.getVertexSetSize() << " vertices." << endl;
    out << "These vertices are" << endl;
    for (int i = 0; i < g.getVertexSetSize(); i++)
    {
        Vertex v = g.V[i];
        out << "Vertex at index " << i << " = " << v.getName() << endl;
    }
    out << endl;
    out << "Each vertex together with its edge set looks like as follows" << endl;
    for (int i = 0; i < g.getVertexSetSize(); i++)
    {
        Vertex v = g.V[i];
        out << v << endl;
    }
    out << endl;
    out << "The graph connectivities are as follows..." << endl;
    out.setf(ios::fixed | ios::left);    //Left aligned fixed decimal places formatting
    for (int i = 0; i < g.getVertexSetSize(); i++)
    {
        Vertex depVertex = g.getVertex(i);
        SmarterArray<Edge> E = depVertex.getEdgeSet();
        for (int j = 0; j < E.getSize(); j++)
        {
            int desVertexIndex = E[j].desVertexIndex;
            Vertex desVertex = g.getVertex(desVertexIndex);
            out << depVertex.getName() << setw(CITY_NAME_WIDTH - depVertex.getName().length()) << " ";
            out << desVertex.getName() << setw(CITY_NAME_WIDTH - desVertex.getName().length()) << " ";
            out << setprecision(2) << E[j].cost << endl;
        }
    }
    out.unsetf(ios::fixed | ios::left);    //Removing formatting
    cout.precision(0);                    //Resetting the decimal places to default
    return out;
}
 
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Path
{
private:
    SmarterArray<CMPT135_String> P; //The names of the vertices along the path
public:
    Path(); //Construct an empty path. Default object P.
    int length() const; //Return the number of vertices along the path (the number of elements of P)
    int find(const CMPT135_String &) const; //Return the index of an element of P whose name matches the
                                            //argument. If no element satisfies the condition, then return -1
                                            //Do not perform assertion operation.
    double computePathCost(const Graph &) const; //Compute the sum of the costs of edges along this path
        //given the underlying Graph argument. Remember that the path object stores only city names. Thus
       //you need the underlying graph argument to determine the vertices in the graph that belong to the
       //cities. Then you will be able to find the edges that connect the vertices which will enable you to
       //get the costs of the edges. The sum of the costs of these edges is returned from this function. If
       //during the computation of the path cost, you find that there is no any edge in the underlying graph
       //that connects successive elements in P, then it means your path is an invalid path and you
       //need to abort your applica``tion.
    CMPT135_String& operator [] (const int &) const; //Assert index is valid and then return the
                                            //element of P at the given index
    void append(const CMPT135_String &); //Append the argument to the calling object. No need to assert.
    void insert(const int &index, const CMPT135_String &); //Assert the condition index >= 0 &&
                                            //index <= the length and then insert the CMPT135_String argument
                                            //at the specified index. If index is equal to the length, then
                                            //perform append.
    void remove(const int &); //Assert the index argument and then remove the element at the specified index
    friend ostream& operator << (ostream &, const Path &); //Implemented for you.
};
Path::Path() : P(SmarterArray<CMPT135_String>()) {}
int Path::length() const { return this->P.getSize(); }
int Path::find(const CMPT135_String &S) const { return this->P.find(S); }
double Path::computePathCost(const Graph &g) const
{
    double travelCost = 0;
    int idep, ides;
    Vertex vertex;
    SmarterArray<Edge> edge;
    for(int i = 0; i < this->length() - 1; i++)
    {
        idep = g.getVertexIndex(P[i]);
        ides = g.getVertexIndex(P[i + 1]);
        vertex = g.getVertex(idep);
        edge = vertex.getEdgeSet();
        int count = 0;
        for(int j = 0; j < edge.getSize(); j++)
        {
            if(edge[j].desVertexIndex == ides)
            {
                count++;
                travelCost = travelCost + edge[j].cost;
            }
        }
        if(count != 1)
        {
            cout << "Wrong path /n";
            abort();
        }
    }
    return travelCost;
}
CMPT135_String& Path::operator [] (const int &index) const
{
    assert(index >= 0 && index < P.getSize());
    return P[index];
}
void Path::append(const CMPT135_String &s) { P.append(s); }
void Path::insert(const int &index, const CMPT135_String &s)
{
    assert(index>=0&&index<=P.getSize());
    P.insert(index,s);
}
void Path::remove(const int &index)
{
    assert(index >= 0 && index < P.getSize());
    P.remove(index);
}
ostream& operator << (ostream &out, const Path &path)
{
    out << "[";
    if (path.length() > 0)
    {
        for (int i = 0; i < path.length()-1; i++)
            out << path[i] << " -> ";
        out << path[path.length()-1];
    }
    out << "]";
    return out;
}
Path computeMinCostPath(const Graph& g, const CMPT135_String &departure, const CMPT135_String& destination, Path &currentPath = Path())
{
    assert(g.getVertexSetSize() > 0);
    int depVertexIndex = g.getVertexIndex(departure);
    int desVertexIndex = g.getVertexIndex(destination);
    assert((depVertexIndex >= 0 && depVertexIndex < g.getVertexSetSize()) && (desVertexIndex >= 0 && desVertexIndex < g.getVertexSetSize()));
    if(departure == destination)
    {
        Path minCostPath = currentPath;
        minCostPath.append(destination);
        cout << minCostPath;
        cout << " with cost ";
        cout << minCostPath.computePathCost(g) << endl;
        return minCostPath;
    }
    else if(currentPath.find(departure) != -1)
    {
        Path minCostPath = currentPath;
        return minCostPath;
    }
    else
    {
        Vertex depVertex = g.getVertex(depVertexIndex);
        SmarterArray<Edge> E = depVertex.getEdgeSet();
        Path minCostPath;
        currentPath.append(departure);
        for(int i = 0; i < E.getSize(); i++)
        {
            Vertex n = g.getVertex(E[i].desVertexIndex);
            CMPT135_String nextVertexName = n.getName();
            if(currentPath.find(nextVertexName)!=-1)
                continue;
            Path candidatePath=computeMinCostPath(g, nextVertexName, destination, currentPath);
            if(candidatePath.length() == 0)
                continue;
            if(candidatePath[candidatePath.length() - 1] != destination)
                continue;
            if(minCostPath.length() == 0)
                minCostPath = candidatePath;
            if(candidatePath.computePathCost(g) < minCostPath.computePathCost(g))
                minCostPath = candidatePath;
        }
        currentPath.remove(currentPath.length() - 1);
        return minCostPath;
    }
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main()
{
    srand(time(0));
    Graph g("/Users/vsharika/Desktop/Connectivity Map.txt");
    cout << "Graph constructed successfully." << endl;
    cout << g << endl;
 
    CMPT135_String departure = g.getRandomVertexName();
    CMPT135_String destination = g.getRandomVertexName();
    cout << "Computing shortest path from " << departure << " to " << destination << endl;
    Path minCostPath = computeMinCostPath(g, departure, destination);
    cout << endl;
    cout << "Departure: " << departure << endl;
    cout << "Destination: " << destination << endl;
    if (minCostPath.length() == 0)
        cout << "No path found." << endl;
    else
        cout << "The minimum cost path is: " << minCostPath << " with cost = " << minCostPath.computePathCost(g) << endl;

    system("Pause");
    return 0;
}
