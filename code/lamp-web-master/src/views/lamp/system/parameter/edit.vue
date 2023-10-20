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
    <el-form :model="parameter" :rules="rules" label-position="right" label-width="100px" ref="form">
      <el-form-item :label="$t('table.parameter.key')"   label="参数名称"  prop="key">
        <el-input :disabled="type==='edit'" type="" v-model="parameter.key" placeholder="参数名称"/> 
       

      </el-form-item>
      <el-form-item :label="$t('table.parameter.name')" label="参数说明" prop="name">
        <el-input type="" v-model="parameter.name" placeholder="参数说明"/>

      </el-form-item>
      <el-form-item :label="$t('table.parameter.value')" label='请求类型' prop="value">
        <el-input type="" v-model="parameter.value" placeholder="请求类型"/>

      </el-form-item>
      <el-form-item :label="$t('table.parameter.describe')" label='数据类型' prop="describe">
        <el-input type="textarea" v-model="parameter.describe" placeholder="数据类型"/>

      </el-form-item>
      <el-form-item :label="$t('table.parameter.schema')" label='schema' prop="schema">
        <el-input type="textarea" v-model="parameter.schema" placeholder="schema"/>

      </el-form-item>
      <el-form-item :label="$t('table.parameter.readonly')" prop="readonly" label='是否必须'  put type="radio">
        <el-radio-group border='true' v-model="parameter.readonly" size="medium">
          <el-radio-button :label="true">{{ $t("common.yes") }}</el-radio-button>
          <el-radio-button :label="false">{{ $t("common.no") }}</el-radio-button>
        </el-radio-group>
      </el-form-item>
    </el-form>
  </el-dialog>
</template>
<script>
import parameterApi from "@/api/Parameter.js";

export default {
  name: "ParameterEdit",
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
      parameter: this.initParameter(),
      screenWidth: 0,
      width: this.initWidth(),
      rules: {
        key: [
          {required: true, message: this.$t("rules.require"), trigger: "blur"},
          { min: 1, max: 255, message: '最多不能超过255字符', trigger: "blur"}
        ],
        name: [
          {required: true, message: this.$t("rules.require"), trigger: "blur"},
          { min: 1, max: 255, message: '最多不能超过255字符', trigger: "blur"}
        ],
        value: [
          { max: 255, message: '最多不能超过255字符', trigger: "blur"}
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
    initParameter() {
      return {
        id: "",
        key: '',
        name: '',
        value: '',
        describe: '',
        readonly: false,
        schema:'',
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
    setParameter(val) {
      const vm = this;
      if (val) {
        vm.parameter = { ...vm.parameter, ...val };
      }
    },
    close() {
      this.$emit("close");
    },
    reset() {
      // 先清除校验，再清除表单，不然有奇怪的bug
      this.$refs.form.clearValidate();
      this.$refs.form.resetFields();
      this.parameter = this.initParameter();
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
      parameterApi.save(this.parameter).then(response => {
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
      parameterApi.update(this.parameter).then(response => {
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
