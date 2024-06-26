- Extract only small part of Eigen project

- Setters at lignes 201-204 added by Yacine Gaoua yg246594 in Eiegen/src/SparseCore/SparseUtil.h

 /** added by Yacine Gaoua **/
  void setRow(const Index& i) { m_row = i; }
  void setCol(const Index& j) { m_col = j; }
  void setValue(const Scalar& v) { m_value = v; }
  
  /** These methods are not used anymore! **/