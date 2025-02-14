#include "header/resulthandler.hpp"

ThisError ResultError::value() const { 
    return ThisError {m_error, m_message};
}