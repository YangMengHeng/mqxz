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
    <el-form :model="encState" :rules="rules" label-position="right" label-width="100px" ref="form">
      <el-form-item :label="$t('table.encState.nodeIp')"   label="节点ip地址"  prop="nodeIp">
        <el-input :disabled="type==='edit'" type="" v-model="encState.nodeIp" placeholder="节点ip地址"/> 
       

      </el-form-item>
      <el-form-item :label="$t('table.encState.nodeName')" label="节点名称" prop="nodeName">
        <el-input type="" v-model="encState.nodeName" placeholder="节点名称"/>

      </el-form-item>
      <el-form-item :label="$t('table.encState.nodePort')" label='节点端口号' prop="nodePort">
        <el-input type="" v-model="encState.nodePort" placeholder="节点端口号"/>

      </el-form-item>
      <el-form-item :label="$t('table.encState.nodeState')" label='节点状态' prop="nodeState">
        <el-input type="textarea" v-model="encState.nodeState" placeholder="节点状态"/>


      </el-form-item>
      
    </el-form>
  </el-dialog>
</template>
<script>
import encStateApi from "@/api/encState.js";

export default {
  name: "encStateEdit",
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
      encState: this.initencState(),
      screenWidth: 0,
      width: this.initWidth(),
      rules: {
        nodeIp: [
          {required: true, message: this.$t("rules.require"), trigger: "blur"},
          { min: 1, max: 255, message: '最多不能超过255字符', trigger: "blur"}
        ],
        nodeName: [
          {required: true, message: this.$t("rules.require"), trigger: "blur"},
          { min: 1, max: 255, message: '最多不能超过255字符', trigger: "blur"}
        ],
        nodePort: [
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
    initencState() {
      return {
        id: "",
        nodeIp: '',
        nodeName: '',
        nodePort: '',
        nodeState: false
       
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
    setencState(val) {
      const vm = this;
      if (val) {
        vm.encState = { ...vm.encState, ...val };
      }
    },
    close() {
      this.$emit("close");
    },
    reset() {
      // 先清除校验，再清除表单，不然有奇怪的bug
      this.$refs.form.clearValidate();
      this.$refs.form.resetFields();
      this.encState = this.initencState();
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
      encStateApi.save(this.encState).then(response => {
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
      encStateApi.update(this.encState).then(response => {
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
