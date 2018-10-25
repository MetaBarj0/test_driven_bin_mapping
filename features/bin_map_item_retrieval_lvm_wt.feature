# language: en

Feature: Bin map item retrieval for the LVM_WT flow

  As a user of Examinator parsers, I need to be able to read a bin map
  file containing bin map items in a tabular format.
  Each bin map item retrieved is specified by a key and exposed as an object
  having its own accessors corresponding to the format of the bin map item
  containing file

  Scenario: Verifying the existence of a LVM_WT bin map item file

    Given the file <file>
    When I check the file exists
    Then the specified file should be reported as existing

  Scenario: Checking the validity of a file by creating a bin map item store

    Given an existing file <file>
    When I create a bin map store from that file
    Then the bin map store should have been created succesfully

  Scenario: Querying a bin map item object from a store

    Given a bin map item store created from an existing file <file>
    When I query a bin map item using the key 5
    Then the bin map item should have been retrieved successfully

  Scenario Outline: Getting properties of a retrieved bin map item

    Given a bin map item store created from an existing file <file>
    When I query a bin map item using the key <key>
    Then the bin map item should have been retrieved successfully
    And the test name should be <test_name>
    And the binning number should be <bin_number>
    And the binning name should be <bin_name>

  Examples:
    | file                       | key | test_name | bin_number | bin_name  |
    | ./bin_map_items_lvm_wt.csv | 5   | GS SHORT  | 29         | GS SHORT  |
    | ./bin_map_items_lvm_wt.csv | 53  | DS SHORT  | 30         | DS SHORT  |
    | ./bin_map_items_lvm_wt.csv | 26  | Vth(OPEN) | 31         | Vth(OPEN) |
    | ./bin_map_items_lvm_wt.csv | 103 | UIS       | 5          | UIS       |
