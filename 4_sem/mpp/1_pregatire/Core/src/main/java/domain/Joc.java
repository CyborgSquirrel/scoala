package domain;

import javax.persistence.Column;
import javax.persistence.GeneratedValue;
import javax.persistence.GenerationType;
import javax.persistence.Id;
import java.util.Objects;

@javax.persistence.Entity
@javax.persistence.Table(name = "Joc")
public class Joc implements Entity<Integer> {
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    int id;

    Integer jucator0Id;
    String jucator0Cuvant;

    Integer jucator1Id;
    String jucator1Cuvant;

    Integer jucator2Id;
    String jucator2Cuvant;

    public Joc() {

    }

    @Override
    public Integer getId() {
        return id;
    }

    @Override
    public void setId(Integer id) {
        this.id = id;
    }

    public int getJucatoriCount() {
        int jucatoriCount = 0;
        for (int i = 0; i < 3; ++i) {
            if (getJucatorId(i) != null) {
                jucatoriCount += 1;
            }
        }
        return jucatoriCount;
    }

    public Integer getJucatorId(int index) {
        switch (index) {
            case 0: {
                return jucator0Id;
            }
            case 1: {
                return jucator1Id;
            }
            case 2: {
                return jucator2Id;
            }
        }
        return null;
    }

    public String getJucatorCuvant(int index) {
        switch (index) {
            case 0: {
                return jucator0Cuvant;
            }
            case 1: {
                return jucator1Cuvant;
            }
            case 2: {
                return jucator2Cuvant;
            }
        }
        return null;
    }

    public void addJucator(int jucatorId, String jucatorCuvant) {
        if (jucator0Id == null) {
            jucator0Id = jucatorId;
            jucator0Cuvant = jucatorCuvant;
        } else if (jucator1Id == null) {
            jucator1Id = jucatorId;
            jucator1Cuvant = jucatorCuvant;
        } else if (jucator2Id == null) {
            jucator2Id = jucatorId;
            jucator2Cuvant = jucatorCuvant;
        } else {
            assert false;
        }
    }

    public void removeJucatorByIndex(int index) {
        if (index >= 0) {
            jucator0Id = jucator1Id;
            jucator0Cuvant = jucator1Cuvant;
        }

        if (index >= 1) {
            jucator1Id = jucator2Id;
            jucator1Cuvant = jucator2Cuvant;
        }

        jucator2Id = null;
        jucator2Cuvant = null;
    }

    public Integer getJucatorIndexById(Integer jucatorId) {
        for (int i = 0; i < 3; ++i) {
            if (Objects.equals(getJucatorId(i), jucatorId)) {
                return i;
            }
        }
        return null;
    }
}
