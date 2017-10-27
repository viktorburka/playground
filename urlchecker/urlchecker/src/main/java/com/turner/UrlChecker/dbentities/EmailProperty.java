package com.turner.UrlChecker.dbentities;

/**
 * This class represents email property
 * database record as Java class.
 */
public class EmailProperty {

    private String name;
    private String value;

    public EmailProperty(String name, String value) {
        this.name = name;
        this.value = value;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getValue() {
        return value;
    }

    public void setValue(String value) {
        this.value = value;
    }
}
