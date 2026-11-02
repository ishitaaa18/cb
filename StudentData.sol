// SPDX-License-Identifier: MIT
pragma solidity ^0.8.0;

contract StudentData {

    struct Student {
        uint id;
        string name;
        uint age;
        string course;
    }

    Student[] public students;

    function addStudent(
        uint _id,
        string memory _name,
        uint _age,
        string memory _course
    ) public {
        students.push(Student(_id, _name, _age, _course));
    }

    function getStudent(uint index)
        public
        view
        returns (uint, string memory, uint, string memory)
    {
        Student memory s = students[index];
        return (s.id, s.name, s.age, s.course);
    }

    function getStudentCount() public view returns (uint) {
        return students.length;
    }
}