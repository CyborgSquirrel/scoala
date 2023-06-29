package repo;

public class SqlUtil {
    private static final boolean DO_LOGGING = true;

    private String tableName;
    private String[] idColumns;
    private String[] dataColumns;

    public SqlUtil(String tableName, String[] idColumns, String[] dataColumns) {
        this.tableName = tableName;
        this.idColumns = idColumns;
        this.dataColumns = dataColumns;
    }

    String makeFind() {
        StringBuilder sql = new StringBuilder();

        sql.append("SELECT");

        sql.append(" ");

        {
            boolean needComma = false;
            for (String idColumn : idColumns) {
                if (needComma) {
                    sql.append(",");
                } else {
                    needComma = true;
                }
                sql.append(idColumn);
            }
            for (String dataColumn : dataColumns) {
                if (needComma) {
                    sql.append(",");
                } else {
                    needComma = true;
                }
                sql.append(dataColumn);
            }
        }
        sql.append(" ");

        sql.append("FROM");

        sql.append(" ");

        sql.append(tableName);

        sql.append(" ");

        sql.append("WHERE");

        sql.append(" ");

        {
            boolean needComma = false;
            for (String idColumn : idColumns) {
                if (needComma) {
                    sql.append(",");
                } else {
                    needComma = true;
                }
                sql.append(idColumn);
                sql.append("=");
                sql.append("?");
            }
        }

        if (DO_LOGGING) {
            System.out.println(sql.toString());
        }

        return sql.toString();
    }

    String makeStore() {
        StringBuilder sql = new StringBuilder();
        sql.append("INSERT INTO");

        sql.append(" ");

        sql.append(tableName);

        sql.append("(");
        {
            boolean needComma = false;
            for (String dataColumn : dataColumns) {
                if (needComma) {
                    sql.append(",");
                } else {
                    needComma = true;
                }
                sql.append(dataColumn);
            }
        }
        sql.append(")");

        sql.append("VALUES");

        sql.append("(");
        {
            boolean needComma = false;
            for (String dataColumn : dataColumns) {
                if (needComma) {
                    sql.append(",");
                } else {
                    needComma = true;
                }
                sql.append("?");
            }
        }
        sql.append(")");

        sql.append(" ");

        sql.append("RETURNING");

        sql.append(" ");

        {
            boolean needComma = false;
            for (String idColumn : idColumns) {
                if (needComma) {
                    sql.append(",");
                } else {
                    needComma = true;
                }
                sql.append(idColumn);
            }
        }

        if (DO_LOGGING) {
            System.out.println(sql.toString());
        }

        return sql.toString();
    }

    String makeUpdate() {
        StringBuilder sql = new StringBuilder();
        sql.append("UPDATE");

        sql.append(" ");

        sql.append(tableName);

        sql.append(" ");

        sql.append("SET");

        sql.append(" ");

        {
            boolean needComma = false;
            for (String dataColumn : dataColumns) {
                if (needComma) {
                    sql.append(",");
                } else {
                    needComma = true;
                }
                sql.append(dataColumn);
                sql.append("=");
                sql.append("?");
            }
        }

        sql.append(" ");

        sql.append("WHERE");

        sql.append(" ");

        {
            boolean needComma = false;
            for (String idColumn : idColumns) {
                if (needComma) {
                    sql.append(",");
                } else {
                    needComma = true;
                }
                sql.append(idColumn);
                sql.append("=");
                sql.append("?");
            }
        }

        if (DO_LOGGING) {
            System.out.println(sql.toString());
        }

        return sql.toString();
    }

    String makeRemove() {
        StringBuilder sql = new StringBuilder();
        sql.append("DELETE FROM");

        sql.append(" ");

        sql.append(tableName);

        sql.append(" ");

        sql.append("WHERE");

        sql.append(" ");

        {
            boolean needComma = false;
            for (String idColumn : idColumns) {
                if (needComma) {
                    sql.append(",");
                } else {
                    needComma = true;
                }
                sql.append(idColumn);
                sql.append("=");
                sql.append("?");
            }
        }

        if (DO_LOGGING) {
            System.out.println(sql.toString());
        }

        return sql.toString();
    }

    String makeGetAll() {
        StringBuilder sql = new StringBuilder();

        sql.append("SELECT");

        sql.append(" ");

        {
            boolean needComma = false;
            for (String idColumn : idColumns) {
                if (needComma) {
                    sql.append(",");
                } else {
                    needComma = true;
                }
                sql.append(idColumn);
            }
            for (String dataColumn : dataColumns) {
                if (needComma) {
                    sql.append(",");
                } else {
                    needComma = true;
                }
                sql.append(dataColumn);
            }
        }
        sql.append(" ");

        sql.append("FROM");

        sql.append(" ");

        sql.append(tableName);

        if (DO_LOGGING) {
            System.out.println(sql.toString());
        }

        return sql.toString();
    }
}
