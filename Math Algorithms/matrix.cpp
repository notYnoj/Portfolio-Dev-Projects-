#include <iostream>
#include <vector>
#include <stdexcept>
#include <utility>
#include <float.h>

struct Matrix{
public:
    size_t rows, columns;
    std::vector<double> data;
    Matrix(const size_t& rows, const size_t& columns) : rows(rows), columns(columns) {
        data.resize(rows*columns);
    }
    /*
    Goal of Matrix:
    Matrix y Done
    Append Information with row, col Done
    Add two matrixes together Done
    Multiply by a Scalar Done
    Subtract two matrixes together (This can be done by scalar by -1 then add) Done
    Matrix Multiplication Done
    Transpose Done
    
    Square Matrices:
    Det DONE
    Inverse 
     */
    void append(size_t row, size_t col, double value){
        if(row >= rows || col >= columns){
            throw std::out_of_range("You are trying to insert an element that doesn't exist");
        }
        data[row * columns + col] = value;
    }

    double get(size_t row, size_t col) const{
        return data[row * columns + col];
    }
    
    Matrix operator+(const Matrix& Addend) const{
        if(Addend.rows != rows || Addend.columns != columns){
            throw std::invalid_argument("Addend Matrix does not have the same dimensions");
        }
        Matrix temp(rows, columns);
        for(size_t index{}; index < rows * columns; index++){
            temp.data[index] = data[index] + Addend.data[index];
        }
        return temp;
    }

    Matrix& operator+=(const Matrix& Addend){
        if(Addend.rows != rows || Addend.columns != columns){
            throw std::invalid_argument("Addend Matrix does not have the same dimensions");
        }
        for(size_t index{}; index < rows * columns; index++){
            data[index] = data[index] + Addend.data[index];
        }
        return *this;
    }
    
    Matrix operator*(const double& scalar) const {
        Matrix temp(rows, columns);
        for(size_t index{}; index < rows * columns; index++){
            if(data[index] > (DBL_MAX / scalar)){
                throw std::overflow_error("Overflow Error when attempting scalar multiplication. Index: " + std::to_string(index) + " Scalar: " + std::to_string(scalar));
            }
            temp.data[index] = data[index] * scalar;
        }
        return temp;
    }

    friend Matrix operator*(double scalar, const Matrix& mat) {
        return mat * scalar;
    }

    Matrix& operator*=(const double& scalar){
        for(size_t index{}; index < rows * columns; index++){
            if(data[index]>DBL_MAX / scalar){
                throw std::overflow_error("Overflow Error when attempting scalar multiplication. Index: " + std::to_string(index) + " Scalar: " + std::to_string(scalar));
            }
            data[index] *= scalar;
        }
        return *this;
    }

    Matrix operator-(const Matrix& Subtrahend) const{
        if(Subtrahend.rows != rows || Subtrahend.columns != columns){
            throw std::invalid_argument("Subtrahend Matrix does not have the same dimensions");
        }
        return (*this + (Subtrahend * -1.0));
    }

    Matrix& operator -=(const Matrix& Subtrahend){
        if(Subtrahend.rows != rows || Subtrahend.columns != columns){
            throw std::invalid_argument("Subtrahend Matrix does not have the same dimensions");
        }
        return *this += (Subtrahend * -1.0);
    }

    Matrix operator*(const Matrix& Factor) const{
        //Mat(a) * Mat(b) -> a.cols = b.rows
        if(columns != Factor.rows){
            throw std::invalid_argument("You can not multiply matrixes where first matrix rows != second matrix columns");
        }
        Matrix temp(rows, Factor.columns);
        //row 1 all cols  * all rows col 1
        for(size_t index{}; index < rows; index++){
            for(size_t index2{}; index2 < Factor.columns; index2++){
                double ans = 0;
                for(size_t index3{}; index3 < columns; index3++){
                    ans += (get(index, index3) * Factor.get(index3, index2));
                }
                temp.append(index, index2, ans);
            }
        }
        return temp;
    }

    Matrix& operator*=(const Matrix& Factor){
        *this = *this * Factor;  // Don't need the temp variable
        return *this;
    }

    Matrix T()const{
        Matrix answer(columns, rows);
        for(size_t row{}; row < rows; row++){
            for(size_t col{}; col < columns; col++){
                answer.append(col, row, data[row * columns + col]);
            }
        }
        return answer;
    }
    
    /*We could do cofactor expansion where we just go A*det(below) - B det(below) and stuff (really easy recursive implementation) but thats O(N!)
    So, let's instead learn about LU decompositon real quick and then implement that*/
    std::pair<Matrix, Matrix> LU_Decomposition() const{
        if(rows != columns){
            throw(std::invalid_argument("You need a square matrix to take a determinant"));
        }
        Matrix L(rows, columns);
        Matrix U = *this;
        for(size_t i{}; i < rows; i++){
            L.append(i, i, 1);
        }
        //we are going to solve for L basically and iterate via columns
        for(size_t col{}; col < columns; col++){
            if(U.get(col, col)  == 0){
                throw std::runtime_error("LU decomposition failed because matrix is singular");
            }
            for(size_t row{col+1}; row < rows; row++){
                //above is 1 so we get that d/a so we want U[row, col]/u[row, row]
                L.append(row, col, (U.get(row, col) / U.get(col, col))); // then change u's cur row
                //pivot's row gets changed
                for(size_t U_COL{col}; U_COL < columns; U_COL++){
                    //get row,ucol -= whatever we just appened*u(col, U_COL) [row is wrong becuz we start row one more down]
                    U.append(row, U_COL, (U.get(row, U_COL) - L.get(row, col) * U.get(col,U_COL)));
                }
            }
        }
        return {L, U};
    }

    double det() const{
        //Okay I'm back - So I learned that the det(triagular matrix) = product of diagonals <- If u forget why: work thru with an example of a 3x3 then generalize using factor expansion
        //Okay so now we need to implement this strategy
        if(rows != columns){
            throw(std::invalid_argument("You need a square matrix to take a determinant"));
        }
        try {
            Matrix U = LU_Decomposition().second;
            double determinant = 1;
            for(size_t i{}; i < rows; i++){
                determinant *= U.get(i, i);
            }
            return determinant;
        } catch(const std::runtime_error& e) {
            return 0.0;
        }
    }

    Matrix adj() const{
        //TO BE IMPLEMENTED
        return Matrix(0,0);
    }

    Matrix inv() const{
        if(rows != columns){
            throw(std::invalid_argument("You need a square matrix to have an inverse"));
        }
        //1/det * adj(Matrix) -> check if det != 0 
        double determinant = det();
        if(determinant == 0){
            throw std::runtime_error("Matrix is not invertible as determinant is zero");
        }
        return ((1 / determinant) * adj());
    }

};