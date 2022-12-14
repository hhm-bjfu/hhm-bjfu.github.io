```sql
数据库测试
DDL语句
学术活动表：
CREATE TABLE `tb_activity`  (
  `activity_id` int(11) NOT NULL AUTO_INCREMENT COMMENT 'uid',
  `activity_name` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL COMMENT '活动名称',
  `country` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL COMMENT '活动地点的国家',
  `province` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL COMMENT '省',
  `city` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL COMMENT '市',
  `address` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL COMMENT '详细地址',
  `activity_time` date NOT NULL COMMENT '活动时间',
  PRIMARY KEY (`activity_id`) USING BTREE
)

附件表：
CREATE TABLE `tb_appex`  (
  `appex_id` int(11) NOT NULL AUTO_INCREMENT COMMENT 'uid',
  `appex_name` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL COMMENT '附件名称',
  `URL` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL COMMENT '附件URL',
  PRIMARY KEY (`appex_id`) USING BTREE
)

学院表：
CREATE TABLE `tb_college`  (
  `college_id` int(11) NOT NULL AUTO_INCREMENT COMMENT 'uid',
  `college_name` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL COMMENT '学院名',
  `overview` text CHARACTER SET utf8 COLLATE utf8_general_ci NULL COMMENT '学院概述',
  PRIMARY KEY (`college_id`) USING BTREE
)

课程表：
CREATE TABLE `tb_course`  (
  `course_id` int(32) NOT NULL AUTO_INCREMENT COMMENT '课程号',
  `subject_id` int(32) NOT NULL COMMENT '所属学科id',
  `course_name` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL COMMENT '课程名',
  `course_hour` int(3) NOT NULL COMMENT '课程学时',
  `student_num` int(5) NOT NULL COMMENT '课程人数',
  `nature` enum('必修课','选修课') CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL COMMENT '课程性质(必修/选修)',
  `object` enum('本科生','研究生') CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL COMMENT '授课对象(本科生/研究生)',
  `term` int(2) NOT NULL COMMENT '开设学期',
  `year` varchar(50) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL COMMENT '开设年度',
  PRIMARY KEY (`course_id`) USING BTREE,
  INDEX `course_s`(`subject_id`) USING BTREE,
  INDEX `course_t`(`term`) USING BTREE,
  CONSTRAINT `course_s` FOREIGN KEY (`subject_id`) REFERENCES `tb_subject` (`subject_id`) ON DELETE RESTRICT ON UPDATE RESTRICT
)


登录信息表：
CREATE TABLE `tb_login`  (
  `login_id` int(11) NOT NULL AUTO_INCREMENT COMMENT 'uid',
  `role` int(3) NOT NULL COMMENT '登录身份',
  `user_id` varchar(50) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL COMMENT '输入的用户名',
  `password` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL COMMENT '输入密码',
  `status` varchar(10) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL COMMENT '登录状态',
  `login_time` datetime(0) NOT NULL COMMENT '登录时间',
  `login_ip` varchar(15) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL COMMENT '登录ip',
  PRIMARY KEY (`login_id`) USING BTREE,
  INDEX `login_u`(`user_id`) USING BTREE
)


学生项目表：
CREATE TABLE `tb_pro_student`  (
  `pro_student_id` int(11) NOT NULL AUTO_INCREMENT COMMENT 'uid',
  `project_id` int(11) NOT NULL COMMENT '项目ID',
  `student_id` varchar(50) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL COMMENT '学号',
  `funding` decimal(8, 2) NULL DEFAULT NULL COMMENT '承担工作折合经费',
  `start_time` date NOT NULL COMMENT '学生开始时间',
  `end_time` date NOT NULL COMMENT '学生结束时间',
  `task` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL COMMENT '承担工作',
  `audit_status` int(2) NOT NULL DEFAULT 0 COMMENT '审核状态（0代表未审核，1代表只有导师审核完成，2代表只有项目负责人审核完成，3代表两者均审核完成）',
  `manager_audit_time` datetime(0) NULL DEFAULT NULL COMMENT '项目负责人审批时间',
  `teacher_audit_time` datetime(0) NULL DEFAULT NULL COMMENT '导师审批时间',
  PRIMARY KEY (`pro_student_id`) USING BTREE,
  INDEX `pro_student_p`(`project_id`) USING BTREE,
  INDEX `pro_student_s`(`student_id`) USING BTREE,
  CONSTRAINT `pro_student_p` FOREIGN KEY (`project_id`) REFERENCES `tb_project` (`project_id`) ON DELETE RESTRICT ON UPDATE RESTRICT,
  CONSTRAINT `pro_student_s` FOREIGN KEY (`student_id`) REFERENCES `tb_student` (`student_id`) ON DELETE RESTRICT ON UPDATE RESTRICT
)


教师项目表：
CREATE TABLE `tb_pro_teacher`  (
  `pro_teacher_id` int(11) NOT NULL AUTO_INCREMENT COMMENT 'uid',
  `project_id` int(11) NOT NULL COMMENT '项目ID',
  `teacher_id` varchar(50) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL COMMENT '教师ID',
  `ismanager` int(1) NOT NULL DEFAULT 0 COMMENT '是否是项目负责人（0代表不是，1代表是）',
  PRIMARY KEY (`pro_teacher_id`) USING BTREE,
  UNIQUE INDEX `pro_teacher_unique`(`project_id`, `teacher_id`) USING BTREE,
  INDEX `pro_teacher_p`(`project_id`) USING BTREE,
  INDEX `pro_teacher_t`(`teacher_id`) USING BTREE,
  CONSTRAINT `pro_teacher_p` FOREIGN KEY (`project_id`) REFERENCES `tb_project` (`project_id`) ON DELETE RESTRICT ON UPDATE RESTRICT,
  CONSTRAINT `pro_teacher_t` FOREIGN KEY (`teacher_id`) REFERENCES `tb_teacher` (`teacher_id`) ON DELETE RESTRICT ON UPDATE RESTRICT
)


项目类型表：
CREATE TABLE `tb_pro_type`  (
  `pro_type_id` int(11) NOT NULL AUTO_INCREMENT COMMENT 'uid',
  `type_name` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL COMMENT '项目类别名称',
  PRIMARY KEY (`pro_type_id`) USING BTREE
)


项目表：
CREATE TABLE `tb_project`  (
  `project_id` int(11) NOT NULL AUTO_INCREMENT COMMENT 'uid',
  `project_name` varchar(200) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL COMMENT '项目名称',
  `type_id` int(11) NOT NULL COMMENT '项目类别ID',
  `start_time` date NOT NULL COMMENT '项目开始时间',
  `end_time` date NOT NULL COMMENT '项目结束时间',
  `funding` decimal(8, 2) NOT NULL COMMENT '项目经费',
  PRIMARY KEY (`project_id`) USING BTREE,
  INDEX `project_t`(`type_id`) USING BTREE,
  CONSTRAINT `project_t` FOREIGN KEY (`type_id`) REFERENCES `tb_pro_type` (`pro_type_id`) ON DELETE RESTRICT ON UPDATE RESTRICT
)


学术报告表：
CREATE TABLE `tb_report`  (
  `report_id` int(11) NOT NULL AUTO_INCREMENT COMMENT 'uid',
  `student_id` varchar(50) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL COMMENT '学号',
  `activity_id` int(11) NOT NULL COMMENT '活动号',
  `chinese_name` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL COMMENT '报告中文名称',
  `english_name` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL COMMENT '报告英文名称',
  `audit_status` int(2) NOT NULL DEFAULT 0 COMMENT '审核状态（0代表未审核，1代表只有导师审核完成，2代表只有学科负责人审核完成，3代表两者均审核完成）',
  `mteacher_audit_time` datetime(0) NULL DEFAULT NULL COMMENT '学科负责人审核时间',
  `teacher_audit_time` datetime(0) NULL DEFAULT NULL COMMENT '导师审核时间',
  `appex_id` int(11) NULL DEFAULT NULL COMMENT '证明材料附件ID',
  `activity_description` longtext CHARACTER SET utf8 COLLATE utf8_general_ci NULL COMMENT '对学术活动的描述',
  `process_description` longtext CHARACTER SET utf8 COLLATE utf8_general_ci NULL COMMENT '对参会过程的描述',
  PRIMARY KEY (`report_id`) USING BTREE,
  INDEX `report_s`(`student_id`) USING BTREE,
  INDEX `report_ac`(`activity_id`) USING BTREE,
  INDEX `report_ap`(`appex_id`) USING BTREE,
  CONSTRAINT `report_ac` FOREIGN KEY (`activity_id`) REFERENCES `tb_activity` (`activity_id`) ON DELETE RESTRICT ON UPDATE RESTRICT,
  CONSTRAINT `report_ap` FOREIGN KEY (`appex_id`) REFERENCES `tb_appex` (`appex_id`) ON DELETE RESTRICT ON UPDATE RESTRICT,
  CONSTRAINT `report_s` FOREIGN KEY (`student_id`) REFERENCES `tb_student` (`student_id`) ON DELETE RESTRICT ON UPDATE RESTRICT
)


助教课程表：
CREATE TABLE `tb_stu_course`  (
  `stu_course_id` int(11) NOT NULL AUTO_INCREMENT COMMENT 'uid',
  `student_id` varchar(50) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL COMMENT '学号',
  `course_id` int(11) NOT NULL COMMENT '课程ID',
  `teacher_id` varchar(50) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL COMMENT '授课教师ID',
  `evaluation_id` int(11) NULL DEFAULT NULL COMMENT '助教评定ID',
  PRIMARY KEY (`stu_course_id`) USING BTREE,
  UNIQUE INDEX `stu_couse_unique`(`student_id`, `course_id`, `teacher_id`) USING BTREE,
  INDEX `stu_course_s`(`student_id`) USING BTREE,
  INDEX `stu_course_c`(`course_id`) USING BTREE,
  INDEX `stu_course_t`(`teacher_id`) USING BTREE,
  INDEX `stu_course_e`(`evaluation_id`) USING BTREE,
  CONSTRAINT `stu_course_c` FOREIGN KEY (`course_id`) REFERENCES `tb_course` (`course_id`) ON DELETE RESTRICT ON UPDATE RESTRICT,
  CONSTRAINT `stu_course_e` FOREIGN KEY (`evaluation_id`) REFERENCES `tb_stu_evaluation` (`stu_evaluation_id`) ON DELETE RESTRICT ON UPDATE RESTRICT,
  CONSTRAINT `stu_course_s` FOREIGN KEY (`student_id`) REFERENCES `tb_student` (`student_id`) ON DELETE RESTRICT ON UPDATE RESTRICT,
  CONSTRAINT `stu_course_t` FOREIGN KEY (`teacher_id`) REFERENCES `tb_teacher` (`teacher_id`) ON DELETE RESTRICT ON UPDATE RESTRICT
)

助教评价表：
CREATE TABLE `tb_stu_evaluation`  (
  `stu_evaluation_id` int(11) NOT NULL AUTO_INCREMENT COMMENT 'uid',
    
  `self_evaluation` text CHARACTER SET utf8 COLLATE utf8_general_ci NULL COMMENT '助教工作自述',
  `self_evaluation_time` datetime(0) NULL DEFAULT NULL COMMENT '助教自述时间',
  `teacher_evaluation` text CHARACTER SET utf8 COLLATE utf8_general_ci NULL COMMENT '授课教师评价',
  `teacher_evaluate_time` datetime(0) NULL DEFAULT NULL COMMENT '授课教师评定时间',
  `result` varchar(50) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL COMMENT '评定结果',
  PRIMARY KEY (`stu_evaluation_id`) USING BTREE
)


学生表：
CREATE TABLE `tb_student`  (
  `student_id` varchar(50) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL COMMENT '学号',
  `student_name` varchar(200) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL COMMENT '姓名',
  `teacher_id` varchar(50) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL COMMENT '导师ID',
  `subject_id` int(11) NOT NULL COMMENT '所属学科ID',
  `user_id` int(11) NOT NULL COMMENT '对应用户名，外键',
  `student_sex` enum('男','女') CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL COMMENT '性别',
  `birthdate` date NULL DEFAULT NULL COMMENT '出生日期',
  PRIMARY KEY (`student_id`) USING BTREE,
  INDEX `student_t`(`teacher_id`) USING BTREE,
  INDEX `student_s`(`subject_id`) USING BTREE,
  INDEX `student_u`(`user_id`) USING BTREE,
  CONSTRAINT `student_s` FOREIGN KEY (`subject_id`) REFERENCES `tb_subject` (`subject_id`) ON DELETE RESTRICT ON UPDATE RESTRICT,
  CONSTRAINT `student_t` FOREIGN KEY (`teacher_id`) REFERENCES `tb_teacher` (`teacher_id`) ON DELETE RESTRICT ON UPDATE RESTRICT,
  CONSTRAINT `student_u` FOREIGN KEY (`user_id`) REFERENCES `tb_user` (`user_id`) ON DELETE RESTRICT ON UPDATE RESTRICT
)


学科教师表：
CREATE TABLE `tb_sub_teacher`  (
  `sub_teacher_id` int(11) NOT NULL AUTO_INCREMENT COMMENT 'uid',
  `subject_id` int(11) NOT NULL COMMENT '学科id',
  `teacher_id` varchar(50) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL COMMENT '教师号',
  `ismanager` int(1) NOT NULL DEFAULT 0 COMMENT '是否为学科负责人（0代表不是，1代表是）',
  PRIMARY KEY (`sub_teacher_id`) USING BTREE,
  UNIQUE INDEX `sub_teacher_unique`(`subject_id`, `teacher_id`) USING BTREE,
  INDEX `sub_teacher_s`(`subject_id`) USING BTREE,
  INDEX `sub_teacher_t`(`teacher_id`) USING BTREE,
  CONSTRAINT `sub_teacher_s` FOREIGN KEY (`subject_id`) REFERENCES `tb_subject` (`subject_id`) ON DELETE RESTRICT ON UPDATE RESTRICT,
  CONSTRAINT `sub_teacher_t` FOREIGN KEY (`teacher_id`) REFERENCES `tb_teacher` (`teacher_id`) ON DELETE RESTRICT ON UPDATE RESTRICT
)


学科类型表：
CREATE TABLE `tb_sub_type`  (
  `sub_type_id` int(11) NOT NULL AUTO_INCREMENT COMMENT 'uid',
  `type_name` varchar(50) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL COMMENT '学科类别名称',
  PRIMARY KEY (`sub_type_id`) USING BTREE
)


学科表：
CREATE TABLE `tb_subject`  (
  `subject_id` int(11) NOT NULL AUTO_INCREMENT COMMENT 'uid',
  `subject_name` varchar(100) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL COMMENT '学科名',
  `funding_requirement` decimal(8, 2) NOT NULL DEFAULT 10.00 COMMENT '项目经费要求',
  `activity_num` int(4) NOT NULL DEFAULT 2 COMMENT '学术交流次数要求',
  `select_num` int(3) NOT NULL DEFAULT 2 COMMENT '助教志愿可选人数',
  `college_id` int(11) NOT NULL COMMENT '所属学院ID',
  `type_id` int(11) NOT NULL COMMENT '学科类别ID',
  `overview` text CHARACTER SET utf8 COLLATE utf8_general_ci NULL COMMENT '学科概述',
  `teacher_id` varchar(50) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL COMMENT '学科负责人教师ID',
  PRIMARY KEY (`subject_id`) USING BTREE,
  INDEX `subject_c`(`college_id`) USING BTREE,
  INDEX `subject_t`(`type_id`) USING BTREE,
  INDEX `subject_te`(`teacher_id`) USING BTREE,
  CONSTRAINT `subject_c` FOREIGN KEY (`college_id`) REFERENCES `tb_college` (`college_id`) ON DELETE RESTRICT ON UPDATE RESTRICT,
  CONSTRAINT `subject_te` FOREIGN KEY (`teacher_id`) REFERENCES `tb_teacher` (`teacher_id`) ON DELETE RESTRICT ON UPDATE RESTRICT,
  CONSTRAINT `subject_ty` FOREIGN KEY (`type_id`) REFERENCES `tb_sub_type` (`sub_type_id`) ON DELETE RESTRICT ON UPDATE RESTRICT
)


系统培养管理员表：
CREATE TABLE `tb_sys_admin`  (
  `sys_admin_id` varchar(50) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL COMMENT 'uid',
  `sys_admin_name` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL COMMENT '系统培养管理员名称',
  `sex` enum('男','女') CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL COMMENT '性别',
  `birthdate` date NULL DEFAULT NULL COMMENT '出生日期',
  `phone` varchar(20) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL COMMENT '联系方式',
  `email` varchar(80) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL COMMENT '电子邮箱',
  `user_id` int(11) NOT NULL COMMENT 'user_id',
  PRIMARY KEY (`sys_admin_id`) USING BTREE,
  INDEX `sys_admin_u`(`user_id`) USING BTREE,
  CONSTRAINT `sys_admin_u` FOREIGN KEY (`user_id`) REFERENCES `tb_user` (`user_id`) ON DELETE RESTRICT ON UPDATE RESTRICT
)


教师授课表：
CREATE TABLE `tb_tc`  (
  `tc_id` int(11) NOT NULL AUTO_INCREMENT COMMENT 'uid',
  `teacher_id` varchar(32) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL COMMENT '教师号',
  `course_id` int(11) NOT NULL COMMENT '课程ID',
  `need_assistant` int(1) NOT NULL DEFAULT 0 COMMENT '是否需要助教（0代表不需要，1代表需要）',
  `having_assistant` int(1) NOT NULL DEFAULT 0 COMMENT '是否已有助教（0代表不需要，1代表需要）',
  PRIMARY KEY (`tc_id`) USING BTREE,
  UNIQUE INDEX `tc_unique`(`teacher_id`, `course_id`) USING BTREE COMMENT '唯一约束',
  INDEX `tc_t`(`teacher_id`) USING BTREE,
  INDEX `tc_c`(`course_id`) USING BTREE,
  CONSTRAINT `tc_c` FOREIGN KEY (`course_id`) REFERENCES `tb_course` (`course_id`) ON DELETE RESTRICT ON UPDATE RESTRICT,
  CONSTRAINT `tc_t` FOREIGN KEY (`teacher_id`) REFERENCES `tb_teacher` (`teacher_id`) ON DELETE RESTRICT ON UPDATE RESTRICT
)


教师表：
CREATE TABLE `tb_teacher`  (
  `teacher_id` varchar(50) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL COMMENT '教师号',
  `teacher_name` varchar(200) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL COMMENT '姓名',
  `user_id` int(11) NOT NULL COMMENT '用户ID',
  `teacher_sex` enum('男','女') CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL COMMENT '性别',
  `phone` varchar(20) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL COMMENT '联系方式',
  `birthdate` date NULL DEFAULT NULL COMMENT '出生日期',
  `title_id` int(11) NULL DEFAULT NULL COMMENT '职称ID',
  PRIMARY KEY (`teacher_id`) USING BTREE,
  INDEX `teacher_t`(`title_id`) USING BTREE,
  INDEX `teacher_u`(`user_id`) USING BTREE,
  CONSTRAINT `teacher_t` FOREIGN KEY (`title_id`) REFERENCES `tb_title` (`title_id`) ON DELETE RESTRICT ON UPDATE RESTRICT,
  CONSTRAINT `teacher_u` FOREIGN KEY (`user_id`) REFERENCES `tb_user` (`user_id`) ON DELETE RESTRICT ON UPDATE RESTRICT
)


职称表：
CREATE TABLE `tb_title`  (
  `title_id` int(11) NOT NULL AUTO_INCREMENT COMMENT 'uid',
  `title_name` varchar(50) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL COMMENT '职称名称',
  `rank` varchar(50) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL COMMENT '职称级别',
  PRIMARY KEY (`title_id`) USING BTREE
)


用户表：
CREATE TABLE `tb_user`  (
  `user_id` int(11) NOT NULL AUTO_INCREMENT COMMENT '用户ID',
  `password` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL COMMENT '用户密码',
  `role` int(3) NOT NULL COMMENT '用户身份（1代表系统培养管理员，2代表教师，3代表学生）',
  PRIMARY KEY (`user_id`) USING BTREE
)


志愿信息表：
CREATE TABLE `tb_vlt`  (
  `vlt_id` int(11) NOT NULL AUTO_INCREMENT COMMENT 'uid',
  `student_id` varchar(50) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL COMMENT '学号',
  `course_id` int(11) NOT NULL COMMENT '课程ID',
  `select_time` datetime(0) NOT NULL COMMENT '选择时间',
  `rank` int(3) NOT NULL COMMENT '志愿等级',
  `teacher_id` varchar(50) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL COMMENT '授课教师ID',
  PRIMARY KEY (`vlt_id`) USING BTREE,
  INDEX `vlt_s`(`student_id`) USING BTREE,
  INDEX `vlt_c`(`course_id`) USING BTREE,
  INDEX `vlt_t`(`teacher_id`) USING BTREE,
  CONSTRAINT `vlt_c` FOREIGN KEY (`course_id`) REFERENCES `tb_course` (`course_id`) ON DELETE RESTRICT ON UPDATE RESTRICT,
  CONSTRAINT `vlt_s` FOREIGN KEY (`student_id`) REFERENCES `tb_student` (`student_id`) ON DELETE RESTRICT ON UPDATE RESTRICT,
  CONSTRAINT `vlt_t` FOREIGN KEY (`teacher_id`) REFERENCES `tb_teacher` (`teacher_id`) ON DELETE RESTRICT ON UPDATE RESTRICT
)

SQL语句
（1）	用户登录验证的SQL语句
-- 学生登录 
SELECT
* 
FROM
	tb_user AS u,
	tb_student AS s 
WHERE
	role = 2 
	AND u.user_id = s.user_id 
	AND s.student_id = #{student_id} and password=MD5(#{password})

--教师登录 SELECT
* 
FROM
	tb_user AS u,
	tb_teacher as t
WHERE
	role = 1 
	AND u.user_id = t.user_id 
	AND t.teacher_id = #{teacher_id} and password=MD5(#{password})

--系统管理员登录 SELECT
* 
FROM
	tb_user AS u,
	tb_sys_admin AS a 
WHERE
	role = 1
	AND u.user_id = a.user_id 
	AND a.sys_admin_id = #{sys_admin_id} and password=MD5(#{password})
（2）	指定学科和日期范围内助教结果为合格的学生信息相关课程信息
select c.*
from tb_student as s,tb_stu_course as sc,tb_stu_evaluation as se,tb_course as c
where s.student_id=sc.student_id and sc.evaluation_id=se.stu_evaluation_id and se.result="合格" and sc.course_id=c.course_id and c.subject_id=#{subject_id} and se.teacher_evaluate_time between #{begin_time} and #{end_time}
（3）	每名授课教师已经确定的助教总人数
select t.teacher_id,t.teacher_name,count(*)
from tb_stu_course as sc,tb_teacher as t,tb_tc as tc,tb_course as c
where t.teacher_id=tc.teacher_id and tc.course_id=c.course_id and c.course_id=sc.course_id and t.teacher_id=sc.teacher_id
group by t.teacher_id
（4）	指定年度和学科下本科生助教与研究生助教数量差异
select object,count(*)
from tb_course as c,tb_stu_course as sc
where year=#{year} and subject_id=#{subject_id} and sc.course_id=c.course_id
group by object
（5）	指定时间范围内各学科参与国外学术交流的学生信息
select distinct sub.subject_id,sub.subject_name,s.student_id,s.student_name,s.student_sex
from tb_student as s,tb_report as r tb_activity as a,tb_subject as sub
where s.student_id=r.student_id and r.activity_id=a.activity_id and s.subject_id=sub.subject_id and activity_time between #{start_time} and #{end_time} and a.country !=“中国”
group by sub.subject_id
（6）	指定时间范围内某个学科参与国外学术交流的学生人数
select count(s.*)
from tb_student as s,tb_report as r tb_activity as a
where s.student_id=r.student_id and r.activity_id=a.activity_id and activity_time between #{start_time} and #{end_time} and s.subject_id=#{subject_id} and a.country !="中国"
（7）	某个项目已经分配的折合费用
select sum(ps.funding)
from tb_project as p,tb_pro_student as ps
where ps.project_id=p.project_id and p.project_id=#{project_id}
（8）	指定时间范围内某个学科参与经费的总数量
select sum(p.funding)
from tb_sub_teacher as st,tb_teacher as t,tb_pro_teacher as pt,tb_project as p
where st.teacher_id=t.teacher_id and t.teacher_id=pt.teacher_id and p.project_id=pt.project_id and st.subject_id=#{subject_id} and p.start_time between #{start_time} and #{end_time}
（9）	每名导师项目经费总剩余情况
select t.teacher_id,t.teacher_name,sum(p.funding)-sum(ps.funding)
from tb_project as p,tb_pro_student as ps,tb_pro_teacher as pt,tb_teacher as t
where t.teacher_id=pt.teacher_id and pt.project_id=p.project_id and p.project_id=ps.project_id 
group by teacher_id
（10）	指定学生参与项目的基本信息和确认情况
select p.project_id,p.project_name,pt.type_name,ps.start_time,ps.end_time,ps.task,ps.funding,ps.audit_status,ps.manager_audit_time,ps.teacher_audit_time
from tb_pro_student as ps,tb_project as p,tb_pro_type as pt
where ps.project_id=p.project_id and ps.student_id=#{student_id} and p.type_id=pt.type_id
（11）	通过教师身份及教师ID对学科详情进行查询，并且与搜索内容队友且按照给定字段排序
SELECT st2.subject_id,s.subject_name,st.type_name,c.college_name,t.teacher_name
            FROM 
            tb_subject AS s,
            tb_college AS c,
            tb_sub_type AS st,
            tb_sub_teacher AS st2,
            tb_teacher AS t
            WHERE s.type_id=st.sub_type_id 
            AND s.college_id=c.college_id 
            AND st2.teacher_id=#{teacher_id}
            AND st2.`subject_id`=s.`subject_id`
            AND s.teacher_id=t.teacher_id 
            AND s.`subject_name` LIKE #{key}
            AND st2.`ismanager`=1
          
            ORDER BY ${sortBy} ${desc}


（12）通过学生课程ID填写教师评价表，时间为当前时间
update tb_stu_evaluation
            set
            teacher_evaluation=#{teacher_evaluation},
            teacher_evaluate_time=CURRENT_TIME,
            result=#{result}
            where stu_evaluation_id=(
            select sc.evaluation_id
            from tb_stu_course as sc
            where sc.stu_course_id=#{stu_course_id})

（13）通过teacher_id与关键字以及审核状态查询审核案例
select ps.pro_student_id,p.project_id,p.project_name,s.student_id,s.student_name,ps.start_time,ps.end_time,ps.task
            from tb_student as s,tb_pro_student as ps,tb_project as p
            where p.project_id=ps.project_id and ps.student_id=s.student_id and s.teacher_id=#{teacher_id} and (ps.audit_status=0 or ps.audit_status=2)
            and s.student_name LIKE #{key}
（14）通过学科id,审核状态，排序情况查询报告信息。
SELECT r.`report_id`,r.`chinese_name`,r.`english_name`,a.`activity_name`,s.`student_name`
            FROM tb_activity AS a,tb_report AS r,tb_student AS s
            WHERE r.`audit_status` IN(0,1)
            AND r.`activity_id`=a.`activity_id`
            AND r.`student_id`=s.`student_id`
            AND s.`subject_id`=#{subject_id}
      ORDER BY ${sortBy} ${desc}
（15）通过学生id，排序情况，查询该学生的所有项目，并标注是否已完成
select p.project_id,p.project_name,type_name,ps.start_time,ps.end_time,ps.funding,ps.task
 from tb_project as p,tb_pro_student as ps,tb_pro_type as pt
 where pt.pro_type_id=p.type_id and p.project_id=ps.project_id and student_id=#{student_id}
order by ${sortBy} ${desc}
```

