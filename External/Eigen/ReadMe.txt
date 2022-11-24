- Extract only small part of Eigen project

- Setters at lignes 166-169 added by Yacine Gaoua yg246594 in Eiegen/src/SparseCore/SparseUtils.h

 /** added by Yacine Gaoua **/
  void setRow(const Index& i) { m_row = i; }
  void setCol(const Index& j) { m_col = j; }
  void setValue(const Scalar& v) { m_value = v; }