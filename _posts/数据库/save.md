```sql
create database db;
use db

create table tb_stu_evaluation(
    stu_evaluation_id int(11) not null comment "评定id",
    teacher_id varchar(50) character set utf8mb4 collate utf8mb4_general_ci not null comment "教师id",
    stu_course_id int(11) not null comment "终选id",
    self_evaluation text character set utf8mb4 collate utf8mb4_general_ci comment "助教自述评价",
    self_evaluation_time date default null comment "自述时间",
    teacher_evaluation text character set utf8mb4 collate utf8mb4_general_ci comment "授课教师评价",
    teacher_evaluation_time date default null comment "授课教师评价时间",
    result varchar(50) character set utf8mb4 collate utf8mb4_general_ci comment "评价结果",

    constraint tb_stu_evaluation_pk primary key(stu_evaluation_id),
    constraint fk_teacher_id foreign key (teacher_id) references tb_teacher(teacher_id),
    constraint fk_stu_course_id foreign key (stu_course_id) references tb_stu_course(stu_course_id)
);

create table tb_report (
    report_id int(11) not null comment "学术报告id",
    activity_id int(11) not null comment "学术活动id",
    student_id varchar(50) character set utf8mb4 collate utf8mb4_general_ci not null comment "学生id",
    teacher_id varchar(50) character set utf8mb4 collate utf8mb4_general_ci not null comment "教师id",
    chinese_name varchar(50) character set utf8mb4 collate utf8mb4_general_ci not null comment "报告中文名称",
    english_name varchar(50) character set utf8mb4 collate utf8mb4_general_ci not null comment "报告英文名称",
    audit_status int(2) default '0' comment "审核状态",
    remark longtext character set utf8mb4 collate utf8mb4_general_ci comment "备注",
    teacher_audit_time date default null comment "报告导师审批时间",
    mteacher_audit_time date default null comment "学科负责人审批时间",
    activity_description longtext character set utf8mb4 collate utf8mb4_general_ci comment "学术活动描述",
    process_description longtext character set utf8mb4 collate utf8mb4_general_ci comment "参会过程描述",

    constraint tb_report_pk primary key(report_id),
    constraint fk_activity_id foreign key(activity_id) references tb_activity(activity_id),
    constraint fk_student_id foreign key (student_id) references tb_student(student_id),
    constraint fk_teacher_id foreign key (teacher_id) references tb_teacher(teacher_id)
);

create table tb_activity (
    activity_id int(11) not null comment "学术活动id",
    activity_name varchar(255) character set utf8mb4 collate utf8mb4_general_ci not null comment "活动名称",
    activity_time date default null comment "活动时间",
    country varchar(255) character set utf8mb4 collate utf8mb4_general_ci comment "国家",
    province varchar(255) character set utf8mb4 collate utf8mb4_general_ci comment "省或州",
    city varchar(255) character set utf8mb4 collate utf8mb4_general_ci comment "市",
    address varchar(255) character set utf8mb4 collate utf8mb4_general_ci comment "详细地址",

    constraint tb_activity_pk primary key(activity_id),
);

create table tb_pro_student (
    project_id int(11) not null comment "项目id",
    pro_student_id int(11) not null comment "学术项目id",
    student_id varchar(50) character set utf8mb4 collate utf8mb4_general_ci not null comment "学生id",
    task varchar(255) character set utf8mb4 collate utf8mb4_general_ci comment "承担工作",
    funding decimal(8, 2) comment "折合经费",
    manager_audit_time date default null comment "项目负责人审批时间",
    mteacher_audit_time date default null comment "学科负责人审批时间",
    start_time date default null comment "学生开始时间",
    end_time date default null comment "学生结束时间",
    audit_status int(2) default '0' comment "审核状态",

    constraint tb_pro_student_pk primary key (project_id),
    constraint fk_student_id foreign key(student_id) references tb_student(student_id)
);

create table tb_subject (
    subject_id int(11) not null comment "学科id",
    college_id int(11) not null comment "学院id",
    type_id int(11) not null comment "学科类别",
    subject_name varchar(100) character set utf8mb4 collate utf8mb4_general_ci comment "学科名称",
    overview text character set utf8mb4 collate utf8mb4_general_ci comment "学科简介",
    select_num int(3) not null comment "志愿可选人数",
    activity_num int(4) not null comment "学术交流次数",
    funding_requirement decimal(8, 2) not null comment "项目经费要求",

    constraint tb_subject_pk primary key (subject_id),
    constraint fk_college_id foreign key (college_id) references tb_college(college_id)
);

create table tb_sub_type (
    subject_type_id int(11) not null comment "学科类别id",
    sub_type_name varchar(50) character set utf8mb4 collate utf8mb4_general_ci comment "学科类别名称",

    constraint tb_sub_type_pk primary key (subject_type_id)
);

create table tb_sub_teacher (
    sub_teacher_id int(11) not null comment "学科教师id",
    teacher_id varchar(50) character set utf8mb4 collate utf8mb4_general_ci not null comment "教师id",
    subject_id int(11) not null comment "学科id",
    ismanager int(1) not null default '0' comment "是否为学科负责人",

    constraint tb_sub_teacher_pk primary key (sub_teacher_id),
    constraint fk_teacher_id foreign key (teacher_id) references tb_teacher(teacher_id),
    constraint fk_subject_id foreign key (subject_id) references tb_subject(subject_id)
);

create table tb_college (
    college_id int(11) not null comment "学院id",
    college_name varchar(255) character set utf8mb4 collate utf8mb4_general_ci not null comment "学院名称",
    overview text character set utf8mb4 collate utf8mb4_general_ci comment "学院简介",

    constraint tb_college_pk primary key (college_id)
);

create table tb_vlt (
    vlt_id int(11) not null comment "志愿选择id",
    teacher_id varchar(50) character set utf8mb4 collate utf8mb4_general_ci not null comment "教师id",
    course_id int(11) not null comment "课程id",
    student_id varchar(50) character set utf8mb4 collate utf8mb4_general_ci not null comment "学生id",
    select_time date default null comment "志愿选择时间",
    rank int(3) not null comment "志愿等级",

    constraint tb_vlt_pk primary key (vlt_id),
    constraint fk_teacher_id foreign key (teacher_id) references tb_teacher(teacher_id),
    constraint fk_course_id foreign key(course_id) references tb_course(course_id),
    constraint fk_student_id foreign key(student_id) references tb_student(student_id)
);

create table tb_tc (
    course_id int(11) not null comment "课程id",
    teacher_id varchar(50) character set utf8mb4 collate utf8mb4_general_ci not null comment "教师id",
    tc_id int(11) not null comment "授课id",
    need_assistant int not null comment "需要助教",
    have_assistant int not null comment "是否有助教",

    constraint fk_teacher_id foreign key (teacher_id) references tb_teacher(teacher_id),
    constraint fk_course_id foreign key(course_id) references tb_course(course_id)
);

create table tb_teacher (
    teacher_id varchar(50) character set utf8mb4 collate utf8mb4_general_ci not null comment "教师id",
    stu_course_id int(11) not null comment "终选id",
    title_id int(11) comment "职称id",
    user_id int(11) not null comment "用户id",
    teacher_name varchar(200) character set utf8mb4 collate utf8mb4_general_ci not null comment "教师名称",
    birthdate date default null comment "出生日期",
    email varchar(60) character set utf8mb4 collate utf8mb4_general_ci not null comment "电子邮件",
    teacher_sex enum('男', '女') comment "教师性别",
    phone varchar(20) character set utf8mb4 collate utf8mb4_general_ci not null comment "联系方式",

    constraint tb_teacher_pk primary key (teacher_id),
    constraint fk_stu_course_id foreign key (stu_course_id) references tb_stu_course(stu_course_id),
    constraint fk_title_id foreign key(title_id) references tb_title(title_id),
    constraint fk_user_id foreign key(user_id) references tb_user(user_id)
);

create table tb_user (
    user_id int(11) not null comment "用户id",
    role int(3) not null comment "身份",
    password varchar(255) character set utf8mb4 collate utf8mb4_general_ci not null comment "密码",

    constraint tb_user_pk primary key (user_id)
);

create table tb_login (
    login_id int(11) not null comment "登录信息id",
    login_time date default null comment "登录时间",
    login_ip varchar(50) character set utf8mb4 collate utf8mb4_general_ci not null comment "登录ip",
    status varchar(10) character set utf8mb4 collate utf8mb4_general_ci not null comment "登录状态",
    password varchar(255) character set utf8mb4 collate utf8mb4_general_ci not null comment "登录密码",
    user_name varchar(50) character set utf8mb4 collate utf8mb4_general_ci not null comment "用户名",
    role int(3) not null comment "登录身份",

    constraint tb_login_pk primary key (login_id)
);

create table tb_student (
    student_id varchar(50) character set utf8mb4 collate utf8mb4_general_ci not null comment "学生id",
    subject_id int(11) not null comment "学科id",
    teacher_id varchar(50) character set utf8mb4 collate utf8mb4_general_ci not null comment "教师id",
    user_id int(11) not null comment "用户id",
    student_name varchar(200) character set utf8mb4 collate utf8mb4_general_ci not null comment "学生姓名",
    enrollment date default null comment "入学年份",
    student_sex enum('男', '女') comment "学生性别",
    birthdate date default null comment "出生日期",

    constraint tb_student_pk primary key (student_id),
    constraint fk_subject_id foreign key (subject_id) references tb_subject(subject_id),
    constraint fk_teacher_id foreign key (teacher_id) references tb_teacher(teacher_id),
    constraint fk_user_id foreign key(user_id) references tb_user(user_id)
);

create table tb_sys_system (
   user_id int(11) not null comment "用户id",

   constraint fk_user_id foreign key(user_id) references tb_user(user_id)
);

create table tb_stu_course (
    stu_course_id int not null,
);

create table tb_course (
    course_id int(11) not null comment "课程id",
);

```

