<!-- springfox-swagger2 -->
<dependency>
    <groupId>io.springfox</groupId>
    <artifactId>springfox-swagger2</artifactId>
    <version>2.9.2</version>
</dependency>
<!-- springfox-swagger-ui -->
<dependency>
    <groupId>io.springfox</groupId>
    <artifactId>springfox-swagger-ui</artifactId>
    <version>2.9.2</version>
</dependency>


@Configuration
@EnableSwagger2
public class SwaggerConfig {

    //配置文档属性
    private ApiInfo getApiInfo(){
      return   new ApiInfoBuilder().title("XX微服务接口文档")
                .description("描述，给前端妹子看的")
                .version("版本1.0")
                .termsOfServiceUrl("http://www.xxx.com")
                .build();
    }
    //创建文档配置对象
    @Bean
    public Docket docket(){
      return   new Docket(DocumentationType.SWAGGER_2).apiInfo(getApiInfo())
                .groupName("group1")
                .select()
                .build();
    }
}



<template>
  <el-dialog
    :close-on-click-modal="false"
    :close-on-press-escape="true"
    :title="title"
    :type="type"
    :visible.sync="isVisible"
    :width="width"
    top="50px">
    <div class="dialog-footer" slot="footer">
      <el-button @click="isVisible = false" plain type="warning">
        {{ $t("common.cancel") }}
      </el-button>
      <el-button @click="submitForm" plain type="primary">
        {{ $t("common.confirm") }}
      </el-button>
    </div>
    <el-form :model="task" :rules="rules" label-position="right" label-width="100px" ref="form">
      <el-form-item :label="$t('table.task.createBy')"   label="创建人"  prop="createBy">
        <el-input :disabled="type==='edit'" type="" v-model="task.createBy" placeholder="创建人"/> 
      </el-form-item>

      <el-form-item :label="$t('table.task.dataUrl')" label="推理数据url" prop="dataUrl">
        <el-input type="" v-model="task.dataUrl" placeholder="推理数据url"/>
      </el-form-item>

      <el-form-item :label="$t('table.task.ecnSelection')" label='推理机选择' prop="ecnSelection">
        <el-input type="" v-model="task.ecnSelection" placeholder="推理机选择"/>
      </el-form-item>

      <el-form-item :label="$t('table.task.endTime')" label='结束时间' prop="endTime" >
        <el-input type="date" v-model="task.endTime" placeholder="结束时间"/>
      </el-form-item>

      <el-form-item :label="$t('table.task.modelParameter')" label='模型参数' prop="modelParameter" >
        <el-input type="textarea" v-model="task.modelParameter" placeholder="模型参数"/>
      </el-form-item>

      <el-form-item :label="$t('table.task.modelSelection')" label='模型选择' prop="modelSelection">
        <el-input type="textarea" v-model="task.modelSelection" placeholder="模型选择"/>
      </el-form-item>

      <el-form-item :label="$t('table.task.startTime')" label='开始时间' prop="startTime" >
        <el-input type="date" v-model="task.startTime" placeholder="开始时间"/>
      </el-form-item>

      <el-form-item :label="$t('table.task.taskName')" label='任务名称' prop="taskName">
        <el-input type="textarea" v-model="task.taskName" placeholder="任务名称"/>


      </el-form-item>
      
    </el-form>
  </el-dialog>
</template>
<script>
import taskApi from "@/api/task.js";

export default {
  name: "taskEdit",
  components: {  },
  props: {
    dialogVisible: {
      type: Boolean,
      default: false
    },
    type: {
      type: String,
      default: "add"
    }
  },
  data() {
    return {
      task: this.inittask(),
      screenWidth: 0,
      width: this.initWidth(),
      rules: {
        createBy: [
          {required: true, message: this.$t("rules.require"), trigger: "blur"},
          { min: 1, max: 255, message: '最多不能超过255字符', trigger: "blur"}
        ],
        dataUrl: [
          {required: true, message: this.$t("rules.require"), trigger: "blur"},
          { min: 1, max: 255, message: '最多不能超过255字符', trigger: "blur"}
        ],
       
      }
    };
  },
  computed: {
    isVisible: {
      get() {
        return this.dialogVisible;
      },
      set() {
        this.close();
        this.reset();
      }
    },
    title() {
      return this.$t("common." + this.type);
    }
  },
  watch: {},
  mounted() {
    window.onresize = () => {
      return (() => {
        this.width = this.initWidth();
      })();
    };
  },
  methods: {
    inittask() {
      return {
        createBy:"",
        dataUrl:"",
        ecnSelection:"",
        endTime: "",
        modelParameter: '',
        modelSelection: '',
        startTime: '',
        taskName: false
      };
    },
    initWidth() {
      this.screenWidth = document.body.clientWidth;
      if (this.screenWidth < 991) {
        return "90%";
      } else if (this.screenWidth < 1400) {
        return "45%";
      } else {
        return "800px";
      }
    },
    settask(val) {
      const vm = this;
      if (val) {
        vm.task = { ...vm.task, ...val };
      }
    },
    close() {
      this.$emit("close");
    },
    reset() {
      // 先清除校验，再清除表单，不然有奇怪的bug
      this.$refs.form.clearValidate();
      this.$refs.form.resetFields();
      this.task = this.inittask();
    },
    submitForm() {
      const vm = this;
      this.$refs.form.validate(valid => {
        if (valid) {
          vm.editSubmit();
        } else {
          return false;
        }
      });
    },
    editSubmit() {
      const vm = this;
      if (vm.type === "edit") {
          vm.update();
  
      } else {
          vm.save();
      }
    },
    save() {
      const vm = this;
      taskApi.save(this.task).then(response => {
        const res = response.data;
        if (res.isSuccess) {
          vm.isVisible = false;
          vm.$message({
            message: vm.$t("tips.createSuccess"),
            type: "success"
          });
          vm.$emit("success");
        }
      });
    },
    update() {
      taskApi.update(this.task).then(response => {
        const res = response.data;
        if (res.isSuccess) {
          this.isVisible = false;
          this.$message({
            message: this.$t("tips.updateSuccess"),
            type: "success"
          });
          this.$emit("success");
        }
      });
    }
  }
};
</script>
<style lang="scss" scoped></style>
